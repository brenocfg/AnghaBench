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
struct wl1251 {int /*<<< orphan*/  (* set_power ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int) ; 

__attribute__((used)) static int wl1251_spi_set_power(struct wl1251 *wl, bool enable)
{
	if (wl->set_power)
		wl->set_power(enable);

	return 0;
}