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
struct pvr2fb_par {scalar_t__ mmio_base; } ;
struct TYPE_2__ {scalar_t__ par; } ;

/* Variables and functions */
 TYPE_1__* fb_info ; 
 int /*<<< orphan*/  fb_writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static inline void pvr2fb_set_pal_type(unsigned int type)
{
	struct pvr2fb_par *par = (struct pvr2fb_par *)fb_info->par;

	fb_writel(type, par->mmio_base + 0x108);
}