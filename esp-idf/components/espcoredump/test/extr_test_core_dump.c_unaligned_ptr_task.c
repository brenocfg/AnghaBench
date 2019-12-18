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

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  recur_func () ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

void unaligned_ptr_task(void *pvParameter)
{
    printf("Task 'unaligned_ptr_task' start.\n");
    while (1) {
        vTaskDelay(1000 / portTICK_RATE_MS);
        printf("Task 'unaligned_ptr_task' run.\n");
        recur_func();
    }
    fflush(stdout);
}