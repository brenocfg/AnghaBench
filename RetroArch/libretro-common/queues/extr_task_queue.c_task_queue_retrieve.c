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
typedef  int /*<<< orphan*/  task_retriever_data_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* retrieve ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_1__* impl_current ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void task_queue_retrieve(task_retriever_data_t *data)
{
   impl_current->retrieve(data);
}