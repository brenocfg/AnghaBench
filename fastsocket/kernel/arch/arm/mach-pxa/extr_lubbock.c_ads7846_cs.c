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
 scalar_t__ PXA2XX_CS_ASSERT ; 
 int /*<<< orphan*/  lubbock_set_misc_wr (unsigned int const,unsigned int const) ; 

__attribute__((used)) static void ads7846_cs(u32 command)
{
	static const unsigned	TS_nCS = 1 << 11;
	lubbock_set_misc_wr(TS_nCS, (command == PXA2XX_CS_ASSERT) ? 0 : TS_nCS);
}