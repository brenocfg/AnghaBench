#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  int /*<<< orphan*/  L3SW ;

/* Variables and functions */
 int /*<<< orphan*/  L3AddIf (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/ * L3AddSw (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  L3SwStart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseL3Sw (int /*<<< orphan*/ *) ; 

void L3Test(SERVER *s)
{
	L3SW *ss = L3AddSw(s->Cedar, "TEST");
	L3AddIf(ss, "DEFAULT", 0x0101a8c0, 0x00ffffff);
	L3AddIf(ss, "DEFAULT2", 0x0102a8c0, 0x00ffffff);
	L3SwStart(ss);
	ReleaseL3Sw(ss);
}