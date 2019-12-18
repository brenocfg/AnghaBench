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
typedef  scalar_t__ uint32_t ;
typedef  int TickType_t ;

/* Variables and functions */
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  xTaskNotifyWait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static bool stopped(void)
{
    uint32_t flag = 0;
    xTaskNotifyWait(0, 0, &flag, (TickType_t) 10/portTICK_RATE_MS);
    return (flag != 0);
}