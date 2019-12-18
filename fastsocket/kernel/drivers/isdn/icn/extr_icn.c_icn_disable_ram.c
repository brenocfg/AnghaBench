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
typedef  int /*<<< orphan*/  icn_card ;

/* Variables and functions */
 int /*<<< orphan*/  ICN_MAPRAM ; 
 int /*<<< orphan*/  OUTB_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
icn_disable_ram(icn_card * card)
{
	OUTB_P(0, ICN_MAPRAM);
}