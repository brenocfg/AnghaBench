#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct connectbundle {int /*<<< orphan*/  conn_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_llist_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct connectbundle*) ; 

__attribute__((used)) static void bundle_destroy(struct connectbundle *cb_ptr)
{
  if(!cb_ptr)
    return;

  Curl_llist_destroy(&cb_ptr->conn_list, NULL);

  free(cb_ptr);
}