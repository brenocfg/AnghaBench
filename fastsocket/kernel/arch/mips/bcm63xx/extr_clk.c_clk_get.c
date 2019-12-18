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
struct device {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 scalar_t__ BCMCPU_IS_6358 () ; 
 int /*<<< orphan*/  ENOENT ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct clk clk_enet0 ; 
 struct clk clk_enet1 ; 
 struct clk clk_ephy ; 
 struct clk clk_pcm ; 
 struct clk clk_periph ; 
 struct clk clk_spi ; 
 struct clk clk_usbh ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

struct clk *clk_get(struct device *dev, const char *id)
{
	if (!strcmp(id, "enet0"))
		return &clk_enet0;
	if (!strcmp(id, "enet1"))
		return &clk_enet1;
	if (!strcmp(id, "ephy"))
		return &clk_ephy;
	if (!strcmp(id, "usbh"))
		return &clk_usbh;
	if (!strcmp(id, "spi"))
		return &clk_spi;
	if (!strcmp(id, "periph"))
		return &clk_periph;
	if (BCMCPU_IS_6358() && !strcmp(id, "pcm"))
		return &clk_pcm;
	return ERR_PTR(-ENOENT);
}