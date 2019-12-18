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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  osi_sem_t ;

/* Variables and functions */
 int OSI_SEM_MAX_TIMEOUT ; 
 scalar_t__ pdTRUE ; 
 int portMAX_DELAY ; 
 int portTICK_PERIOD_MS ; 
 scalar_t__ xSemaphoreTake (int /*<<< orphan*/ ,int) ; 

int
osi_sem_take(osi_sem_t *sem, uint32_t timeout)
{
    int ret = 0;

    if (timeout ==  OSI_SEM_MAX_TIMEOUT) {
        if (xSemaphoreTake(*sem, portMAX_DELAY) != pdTRUE) {
            ret = -1;
        }
    } else {
        if (xSemaphoreTake(*sem, timeout / portTICK_PERIOD_MS) != pdTRUE) {
            ret = -2;
        }
    }

    return ret;
}