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
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  error ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int rand () ; 
 int /*<<< orphan*/  srand (int) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tskTestRand(void *pvParameters)
{
    int l;
    srand(0x1234);
    vTaskDelay((int)pvParameters / portTICK_PERIOD_MS);
    l = rand();
    printf("Rand1: %d\n", l);
    if (l != 869320854) {
        error++;
    }
    vTaskDelay((int)pvParameters / portTICK_PERIOD_MS);
    l = rand();
    printf("Rand2: %d\n", l);
    if (l != 1148737841) {
        error++;
    }
    done++;
    vTaskDelete(NULL);
}