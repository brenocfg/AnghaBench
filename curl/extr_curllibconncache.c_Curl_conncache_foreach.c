#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct curl_llist_element {struct connectdata* ptr; struct curl_llist_element* next; } ;
struct curl_hash_iterator {int dummy; } ;
struct curl_hash_element {struct connectbundle* ptr; } ;
typedef  struct connectdata connectdata ;
struct TYPE_2__ {struct curl_llist_element* head; } ;
struct connectbundle {TYPE_1__ conn_list; } ;
struct conncache {int /*<<< orphan*/  hash; } ;
struct Curl_easy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_LOCK (struct Curl_easy*) ; 
 int /*<<< orphan*/  CONN_UNLOCK (struct Curl_easy*) ; 
 struct curl_hash_element* Curl_hash_next_element (struct curl_hash_iterator*) ; 
 int /*<<< orphan*/  Curl_hash_start_iterate (int /*<<< orphan*/ *,struct curl_hash_iterator*) ; 
 int FALSE ; 
 int TRUE ; 

bool Curl_conncache_foreach(struct Curl_easy *data,
                            struct conncache *connc,
                            void *param,
                            int (*func)(struct connectdata *conn, void *param))
{
  struct curl_hash_iterator iter;
  struct curl_llist_element *curr;
  struct curl_hash_element *he;

  if(!connc)
    return FALSE;

  CONN_LOCK(data);
  Curl_hash_start_iterate(&connc->hash, &iter);

  he = Curl_hash_next_element(&iter);
  while(he) {
    struct connectbundle *bundle;

    bundle = he->ptr;
    he = Curl_hash_next_element(&iter);

    curr = bundle->conn_list.head;
    while(curr) {
      /* Yes, we need to update curr before calling func(), because func()
         might decide to remove the connection */
      struct connectdata *conn = curr->ptr;
      curr = curr->next;

      if(1 == func(conn, param)) {
        CONN_UNLOCK(data);
        return TRUE;
      }
    }
  }
  CONN_UNLOCK(data);
  return FALSE;
}