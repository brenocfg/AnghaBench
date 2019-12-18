#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct ssb_sprom {int boardflags_lo; } ;
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  gmode; } ;
struct b43_wldev {TYPE_2__ phy; TYPE_1__* dev; } ;
struct TYPE_3__ {struct ssb_sprom* bus_sprom; } ;

/* Variables and functions */
 int B43_BFL_BTCMOD ; 
 int B43_BFL_BTCOEXIST ; 
 int /*<<< orphan*/  B43_HF_BTCOEX ; 
 int /*<<< orphan*/  B43_HF_BTCOEXALT ; 
 scalar_t__ B43_PHYTYPE_B ; 
 int /*<<< orphan*/  b43_hf_read (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_hf_write (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modparam_btcoex ; 

__attribute__((used)) static void b43_bluetooth_coext_enable(struct b43_wldev *dev)
{
	struct ssb_sprom *sprom = dev->dev->bus_sprom;
	u64 hf;

	if (!modparam_btcoex)
		return;
	if (!(sprom->boardflags_lo & B43_BFL_BTCOEXIST))
		return;
	if (dev->phy.type != B43_PHYTYPE_B && !dev->phy.gmode)
		return;

	hf = b43_hf_read(dev);
	if (sprom->boardflags_lo & B43_BFL_BTCMOD)
		hf |= B43_HF_BTCOEXALT;
	else
		hf |= B43_HF_BTCOEX;
	b43_hf_write(dev, hf);
}