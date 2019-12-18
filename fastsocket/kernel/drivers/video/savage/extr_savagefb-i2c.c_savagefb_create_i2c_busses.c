#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  getscl; int /*<<< orphan*/  getsda; int /*<<< orphan*/  setscl; int /*<<< orphan*/  setsda; } ;
struct TYPE_8__ {int reg; struct savagefb_par* par; TYPE_3__ algo; int /*<<< orphan*/  ioaddr; } ;
struct TYPE_6__ {int /*<<< orphan*/  vbase; } ;
struct savagefb_par {TYPE_4__ chan; TYPE_2__ mmio; } ;
struct TYPE_5__ {int accel; } ;
struct fb_info {TYPE_1__ fix; struct savagefb_par* par; } ;

/* Variables and functions */
 int CR_SERIAL2 ; 
#define  FB_ACCEL_PROSAVAGE_DDRK 131 
#define  FB_ACCEL_PROSAVAGE_PM 130 
#define  FB_ACCEL_SAVAGE2000 129 
#define  FB_ACCEL_SAVAGE4 128 
 int /*<<< orphan*/  prosavage_gpio_getscl ; 
 int /*<<< orphan*/  prosavage_gpio_getsda ; 
 int /*<<< orphan*/  prosavage_gpio_setscl ; 
 int /*<<< orphan*/  prosavage_gpio_setsda ; 
 int /*<<< orphan*/  savage4_gpio_getscl ; 
 int /*<<< orphan*/  savage4_gpio_getsda ; 
 int /*<<< orphan*/  savage4_gpio_setscl ; 
 int /*<<< orphan*/  savage4_gpio_setsda ; 
 int /*<<< orphan*/  savage_setup_i2c_bus (TYPE_4__*,char*) ; 

void savagefb_create_i2c_busses(struct fb_info *info)
{
	struct savagefb_par *par = info->par;
	par->chan.par	= par;

	switch(info->fix.accel) {
	case FB_ACCEL_PROSAVAGE_DDRK:
	case FB_ACCEL_PROSAVAGE_PM:
		par->chan.reg         = CR_SERIAL2;
		par->chan.ioaddr      = par->mmio.vbase;
		par->chan.algo.setsda = prosavage_gpio_setsda;
		par->chan.algo.setscl = prosavage_gpio_setscl;
		par->chan.algo.getsda = prosavage_gpio_getsda;
		par->chan.algo.getscl = prosavage_gpio_getscl;
		break;
	case FB_ACCEL_SAVAGE4:
	case FB_ACCEL_SAVAGE2000:
		par->chan.reg         = 0xff20;
		par->chan.ioaddr      = par->mmio.vbase;
		par->chan.algo.setsda = savage4_gpio_setsda;
		par->chan.algo.setscl = savage4_gpio_setscl;
		par->chan.algo.getsda = savage4_gpio_getsda;
		par->chan.algo.getscl = savage4_gpio_getscl;
		break;
	default:
		par->chan.par = NULL;
	}

	savage_setup_i2c_bus(&par->chan, "SAVAGE DDC2");
}