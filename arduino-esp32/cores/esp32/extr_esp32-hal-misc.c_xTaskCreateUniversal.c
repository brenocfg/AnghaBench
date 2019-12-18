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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  UBaseType_t ;
typedef  int /*<<< orphan*/  TaskHandle_t ;
typedef  int /*<<< orphan*/  TaskFunction_t ;
typedef  int BaseType_t ;

/* Variables and functions */
 int xTaskCreate (int /*<<< orphan*/ ,char const* const,int /*<<< orphan*/  const,void* const,int /*<<< orphan*/ ,int /*<<< orphan*/ * const) ; 
 int xTaskCreatePinnedToCore (int /*<<< orphan*/ ,char const* const,int /*<<< orphan*/  const,void* const,int /*<<< orphan*/ ,int /*<<< orphan*/ * const,int const) ; 

BaseType_t xTaskCreateUniversal( TaskFunction_t pxTaskCode,
                        const char * const pcName,
                        const uint32_t usStackDepth,
                        void * const pvParameters,
                        UBaseType_t uxPriority,
                        TaskHandle_t * const pxCreatedTask,
                        const BaseType_t xCoreID ){
#ifndef CONFIG_FREERTOS_UNICORE
    if(xCoreID >= 0 && xCoreID < 2) {
        return xTaskCreatePinnedToCore(pxTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask, xCoreID);
    } else {
#endif
    return xTaskCreate(pxTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask);
#ifndef CONFIG_FREERTOS_UNICORE
    }
#endif
}