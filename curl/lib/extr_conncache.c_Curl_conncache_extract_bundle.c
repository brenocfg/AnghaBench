#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ timediff_t ;
struct curltime {int dummy; } ;
struct curl_llist_element {struct curl_llist_element* next; struct connectdata* ptr; } ;
struct connectdata {struct Curl_easy* data; int /*<<< orphan*/  lastused; } ;
struct TYPE_4__ {struct curl_llist_element* head; } ;
struct connectbundle {TYPE_1__ conn_list; } ;
struct TYPE_6__ {TYPE_2__* conn_cache; } ;
struct Curl_easy {TYPE_3__ state; } ;
struct TYPE_5__ {int /*<<< orphan*/  num_conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_INUSE (struct connectdata*) ; 
 struct curltime Curl_now () ; 
 scalar_t__ Curl_timediff (struct curltime,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bundle_remove_conn (struct connectbundle*,struct connectdata*) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,int /*<<< orphan*/ ) ; 

struct connectdata *
Curl_conncache_extract_bundle(struct Curl_easy *data,
                              struct connectbundle *bundle)
{
  struct curl_llist_element *curr;
  timediff_t highscore = -1;
  timediff_t score;
  struct curltime now;
  struct connectdata *conn_candidate = NULL;
  struct connectdata *conn;

  (void)data;

  now = Curl_now();

  curr = bundle->conn_list.head;
  while(curr) {
    conn = curr->ptr;

    if(!CONN_INUSE(conn) && !conn->data) {
      /* Set higher score for the age passed since the connection was used */
      score = Curl_timediff(now, conn->lastused);

      if(score > highscore) {
        highscore = score;
        conn_candidate = conn;
      }
    }
    curr = curr->next;
  }
  if(conn_candidate) {
    /* remove it to prevent another thread from nicking it */
    bundle_remove_conn(bundle, conn_candidate);
    data->state.conn_cache->num_conn--;
    DEBUGF(infof(data, "The cache now contains %zu members\n",
                 data->state.conn_cache->num_conn));
    conn_candidate->data = data; /* associate! */
  }

  return conn_candidate;
}