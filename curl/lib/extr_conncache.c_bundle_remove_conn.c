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
struct curl_llist_element {struct curl_llist_element* next; struct connectdata* ptr; } ;
struct connectdata {int /*<<< orphan*/ * bundle; } ;
struct TYPE_2__ {struct curl_llist_element* head; } ;
struct connectbundle {int /*<<< orphan*/  num_connections; TYPE_1__ conn_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_llist_remove (TYPE_1__*,struct curl_llist_element*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bundle_remove_conn(struct connectbundle *cb_ptr,
                              struct connectdata *conn)
{
  struct curl_llist_element *curr;

  curr = cb_ptr->conn_list.head;
  while(curr) {
    if(curr->ptr == conn) {
      Curl_llist_remove(&cb_ptr->conn_list, curr, NULL);
      cb_ptr->num_connections--;
      conn->bundle = NULL;
      return 1; /* we removed a handle */
    }
    curr = curr->next;
  }
  return 0;
}