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
struct annotate_browser {int /*<<< orphan*/  b; } ;

/* Variables and functions */
 int annotate_browser__jumps_percent_color (struct annotate_browser*,int,int) ; 
 int ui_browser__set_color (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int annotate_browser__set_jumps_percent_color(struct annotate_browser *browser,
						     int nr, bool current)
{
	 int color = annotate_browser__jumps_percent_color(browser, nr, current);
	 return ui_browser__set_color(&browser->b, color);
}