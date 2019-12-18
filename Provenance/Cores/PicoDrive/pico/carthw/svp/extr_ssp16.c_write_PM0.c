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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  EL_SVP ; 
 int /*<<< orphan*/  GET_PPC_OFFS () ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pm_io (int /*<<< orphan*/ ,int,scalar_t__) ; 
 scalar_t__ rPM0 ; 

__attribute__((used)) static void write_PM0(u32 d)
{
	u32 r = pm_io(0, 1, d);
	if (r != (u32)-1) return;
	elprintf(EL_SVP, "PM0 raw w %04x @ %04x", d, GET_PPC_OFFS());
	rPM0 = d;
}