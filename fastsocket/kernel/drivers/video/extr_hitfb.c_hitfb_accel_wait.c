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
 int /*<<< orphan*/  HD64461_GRCFGR ; 
 int HD64461_GRCFGR_ACCSTATUS ; 
 int fb_readw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void hitfb_accel_wait(void)
{
	while (fb_readw(HD64461_GRCFGR) & HD64461_GRCFGR_ACCSTATUS) ;
}