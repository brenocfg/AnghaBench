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
typedef  int u32 ;
struct tg3 {int mi_mode; int /*<<< orphan*/  phy_ape_lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MAC_MI_COM ; 
 int /*<<< orphan*/  MAC_MI_MODE ; 
 int MAC_MI_MODE_AUTO_POLL ; 
 int MI_COM_BUSY ; 
 int MI_COM_CMD_READ ; 
 int MI_COM_DATA_MASK ; 
 unsigned int MI_COM_PHY_ADDR_MASK ; 
 unsigned int MI_COM_PHY_ADDR_SHIFT ; 
 int MI_COM_REG_ADDR_MASK ; 
 int MI_COM_REG_ADDR_SHIFT ; 
 int MI_COM_START ; 
 unsigned int PHY_BUSY_LOOPS ; 
 int /*<<< orphan*/  tg3_ape_lock (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_ape_unlock (struct tg3*,int /*<<< orphan*/ ) ; 
 int tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32_f (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int __tg3_readphy(struct tg3 *tp, unsigned int phy_addr, int reg,
			 u32 *val)
{
	u32 frame_val;
	unsigned int loops;
	int ret;

	if ((tp->mi_mode & MAC_MI_MODE_AUTO_POLL) != 0) {
		tw32_f(MAC_MI_MODE,
		     (tp->mi_mode & ~MAC_MI_MODE_AUTO_POLL));
		udelay(80);
	}

	tg3_ape_lock(tp, tp->phy_ape_lock);

	*val = 0x0;

	frame_val  = ((phy_addr << MI_COM_PHY_ADDR_SHIFT) &
		      MI_COM_PHY_ADDR_MASK);
	frame_val |= ((reg << MI_COM_REG_ADDR_SHIFT) &
		      MI_COM_REG_ADDR_MASK);
	frame_val |= (MI_COM_CMD_READ | MI_COM_START);

	tw32_f(MAC_MI_COM, frame_val);

	loops = PHY_BUSY_LOOPS;
	while (loops != 0) {
		udelay(10);
		frame_val = tr32(MAC_MI_COM);

		if ((frame_val & MI_COM_BUSY) == 0) {
			udelay(5);
			frame_val = tr32(MAC_MI_COM);
			break;
		}
		loops -= 1;
	}

	ret = -EBUSY;
	if (loops != 0) {
		*val = frame_val & MI_COM_DATA_MASK;
		ret = 0;
	}

	if ((tp->mi_mode & MAC_MI_MODE_AUTO_POLL) != 0) {
		tw32_f(MAC_MI_MODE, tp->mi_mode);
		udelay(80);
	}

	tg3_ape_unlock(tp, tp->phy_ape_lock);

	return ret;
}