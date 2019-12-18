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
typedef  int /*<<< orphan*/  SDot11Counters ;
typedef  int /*<<< orphan*/  PSDot11Counters ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
STAvClear802_11Counter(PSDot11Counters p802_11Counter)
{
    // set memory to zero
	memset(p802_11Counter, 0, sizeof(SDot11Counters));
}