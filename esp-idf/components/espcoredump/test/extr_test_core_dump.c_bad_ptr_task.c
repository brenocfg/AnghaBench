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
 int /*<<< orphan*/  bad_ptr_func () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

void bad_ptr_task(void *pvParameter)
{
    printf("Task 'bad_ptr_task' start.\n");
    while (1) {
        vTaskDelay(1000 / portTICK_RATE_MS);
        printf("Task 'bad_ptr_task' run.\n");
        bad_ptr_func();
    }
    fflush(stdout);
}