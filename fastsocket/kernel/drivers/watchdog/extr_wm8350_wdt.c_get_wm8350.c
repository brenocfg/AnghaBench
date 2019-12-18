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
struct wm8350 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct wm8350* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 TYPE_1__ wm8350_wdt_miscdev ; 

__attribute__((used)) static struct wm8350 *get_wm8350(void)
{
	return dev_get_drvdata(wm8350_wdt_miscdev.parent);
}