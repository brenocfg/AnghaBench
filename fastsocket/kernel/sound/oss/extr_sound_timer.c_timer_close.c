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
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  (* tmr_disable ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ opened ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 TYPE_1__* tmr ; 
 scalar_t__ tmr_running ; 

__attribute__((used)) static void timer_close(int dev)
{
	opened = tmr_running = 0;
	tmr->tmr_disable(tmr->dev);
}