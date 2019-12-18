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
struct wl1251 {struct spi_device* if_priv; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct spi_device *wl_to_spi(struct wl1251 *wl)
{
	return wl->if_priv;
}