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
struct TYPE_2__ {scalar_t__ navkeypressed; int /*<<< orphan*/  use_navkeypressed; } ;
struct annotate_browser {int max_jump_sources; TYPE_1__ b; } ;

/* Variables and functions */
 int HE_COLORSET_MEDIUM ; 
 int HE_COLORSET_NORMAL ; 
 int HE_COLORSET_SELECTED ; 
 int HE_COLORSET_TOP ; 

__attribute__((used)) static int annotate_browser__jumps_percent_color(struct annotate_browser *browser,
						 int nr, bool current)
{
	if (current && (!browser->b.use_navkeypressed || browser->b.navkeypressed))
		return HE_COLORSET_SELECTED;
	if (nr == browser->max_jump_sources)
		return HE_COLORSET_TOP;
	if (nr > 1)
		return HE_COLORSET_MEDIUM;
	return HE_COLORSET_NORMAL;
}