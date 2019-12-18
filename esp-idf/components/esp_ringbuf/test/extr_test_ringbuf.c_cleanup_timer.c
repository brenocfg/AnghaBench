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
 int /*<<< orphan*/  TIMER_GROUP ; 
 int /*<<< orphan*/  TIMER_NUMBER ; 
 int /*<<< orphan*/  esp_intr_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ringbuffer_isr_handle ; 
 int /*<<< orphan*/  timer_disable_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup_timer(void)
{
    timer_disable_intr(TIMER_GROUP, TIMER_NUMBER);
    esp_intr_free(ringbuffer_isr_handle);
}