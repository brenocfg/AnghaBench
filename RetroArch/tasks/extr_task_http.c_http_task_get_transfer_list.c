#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  task_retriever_info_t ;
struct TYPE_3__ {int element_size; int /*<<< orphan*/ * list; int /*<<< orphan*/  func; int /*<<< orphan*/  handler; } ;
typedef  TYPE_1__ task_retriever_data_t ;
typedef  int /*<<< orphan*/  http_transfer_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  task_http_retriever ; 
 int /*<<< orphan*/  task_http_transfer_handler ; 
 int /*<<< orphan*/  task_queue_retrieve (TYPE_1__*) ; 

task_retriever_info_t *http_task_get_transfer_list(void)
{
   task_retriever_data_t retrieve_data;

   /* Fill retrieve data */
   retrieve_data.handler      = task_http_transfer_handler;
   retrieve_data.element_size = sizeof(http_transfer_info_t);
   retrieve_data.func         = task_http_retriever;

   /* Build list of current HTTP transfers and return it */
   task_queue_retrieve(&retrieve_data);

   return retrieve_data.list;
}