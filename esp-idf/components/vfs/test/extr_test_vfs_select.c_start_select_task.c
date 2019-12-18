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
typedef  int /*<<< orphan*/  test_select_task_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  select_task ; 
 int /*<<< orphan*/  xTaskCreate (int /*<<< orphan*/ ,char*,int,void*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void inline start_select_task(test_select_task_param_t *param)
{
    xTaskCreate(select_task, "select_task", 4*1024, (void *) param, 5, NULL);
}