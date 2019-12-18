#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int timediff_t ;
struct curltime {int dummy; } ;
struct curl_llist_element {struct curl_llist_element* next; struct connectdata* ptr; } ;
struct curl_hash_iterator {int dummy; } ;
struct curl_hash_element {struct connectbundle* ptr; } ;
struct connectdata {struct Curl_easy* data; int /*<<< orphan*/  lastused; } ;
struct TYPE_4__ {struct curl_llist_element* head; } ;
struct connectbundle {TYPE_2__ conn_list; } ;
struct conncache {int /*<<< orphan*/  num_conn; int /*<<< orphan*/  hash; } ;
struct TYPE_3__ {struct conncache* conn_cache; } ;
struct Curl_easy {TYPE_1__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_INUSE (struct connectdata*) ; 
 int /*<<< orphan*/  CONN_LOCK (struct Curl_easy*) ; 
 int /*<<< orphan*/  CONN_UNLOCK (struct Curl_easy*) ; 
 struct curl_hash_element* Curl_hash_next_element (struct curl_hash_iterator*) ; 
 int /*<<< orphan*/  Curl_hash_start_iterate (int /*<<< orphan*/ *,struct curl_hash_iterator*) ; 
 struct curltime Curl_now () ; 
 int Curl_timediff (struct curltime,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bundle_remove_conn (struct connectbundle*,struct connectdata*) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,int /*<<< orphan*/ ) ; 

struct connectdata *
Curl_conncache_extract_oldest(struct Curl_easy *data)
{
  struct conncache *connc = data->state.conn_cache;
  struct curl_hash_iterator iter;
  struct curl_llist_element *curr;
  struct curl_hash_element *he;
  timediff_t highscore =- 1;
  timediff_t score;
  struct curltime now;
  struct connectdata *conn_candidate = NULL;
  struct connectbundle *bundle;
  struct connectbundle *bundle_candidate = NULL;

  now = Curl_now();

  CONN_LOCK(data);
  Curl_hash_start_iterate(&connc->hash, &iter);

  he = Curl_hash_next_element(&iter);
  while(he) {
    struct connectdata *conn;

    bundle = he->ptr;

    curr = bundle->conn_list.head;
    while(curr) {
      conn = curr->ptr;

      if(!CONN_INUSE(conn) && !conn->data) {
        /* Set higher score for the age passed since the connection was used */
        score = Curl_timediff(now, conn->lastused);

        if(score > highscore) {
          highscore = score;
          conn_candidate = conn;
          bundle_candidate = bundle;
        }
      }
      curr = curr->next;
    }

    he = Curl_hash_next_element(&iter);
  }
  if(conn_candidate) {
    /* remove it to prevent another thread from nicking it */
    bundle_remove_conn(bundle_candidate, conn_candidate);
    connc->num_conn--;
    DEBUGF(infof(data, "The cache now contains %zu members\n",
                 connc->num_conn));
    conn_candidate->data = data; /* associate! */
  }
  CONN_UNLOCK(data);

  return conn_candidate;
}