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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct sh_dmae_chan {int id; } ;

/* Variables and functions */
 scalar_t__ DMARS1_ADDR ; 
 scalar_t__ DMARS2_ADDR ; 
 int DMARS_CHAN_MSK ; 
 int DMARS_SHIFT ; 
 int EINVAL ; 
 scalar_t__ SH_DMARS_BASE ; 
 int ctrl_inw (scalar_t__) ; 
 int /*<<< orphan*/  ctrl_outw (int,scalar_t__) ; 
 int dmae_is_idle (struct sh_dmae_chan*) ; 

__attribute__((used)) static int dmae_set_dmars(struct sh_dmae_chan *sh_chan, u16 val)
{
	u32 addr;
	int shift = 0;
	int ret = dmae_is_idle(sh_chan);
	if (ret)
		return ret;

	if (sh_chan->id & DMARS_CHAN_MSK)
		shift = DMARS_SHIFT;

	switch (sh_chan->id) {
	/* DMARS0 */
	case 0:
	case 1:
		addr = SH_DMARS_BASE;
		break;
	/* DMARS1 */
	case 2:
	case 3:
		addr = (SH_DMARS_BASE + DMARS1_ADDR);
		break;
	/* DMARS2 */
	case 4:
	case 5:
		addr = (SH_DMARS_BASE + DMARS2_ADDR);
		break;
	default:
		return -EINVAL;
	}

	ctrl_outw((val << shift) |
		(ctrl_inw(addr) & (shift ? 0xFF00 : 0x00FF)),
		addr);

	return 0;
}