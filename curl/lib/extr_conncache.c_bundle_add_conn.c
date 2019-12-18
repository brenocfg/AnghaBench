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
struct connectdata {struct connectbundle* bundle; int /*<<< orphan*/  bundle_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  tail; } ;
struct connectbundle {int /*<<< orphan*/  num_connections; TYPE_1__ conn_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_llist_insert_next (TYPE_1__*,int /*<<< orphan*/ ,struct connectdata*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bundle_add_conn(struct connectbundle *cb_ptr,
                            struct connectdata *conn)
{
  Curl_llist_insert_next(&cb_ptr->conn_list, cb_ptr->conn_list.tail, conn,
                         &conn->bundle_node);
  conn->bundle = cb_ptr;
  cb_ptr->num_connections++;
}