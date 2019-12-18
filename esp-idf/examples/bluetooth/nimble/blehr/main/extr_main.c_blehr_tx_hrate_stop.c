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
 int /*<<< orphan*/  blehr_tx_timer ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  xTimerStop (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
blehr_tx_hrate_stop(void)
{
    xTimerStop( blehr_tx_timer, 1000 / portTICK_PERIOD_MS );
}