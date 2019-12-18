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
typedef  int /*<<< orphan*/  u16 ;
struct tg3 {int /*<<< orphan*/  lock; } ;
struct mii_bus {struct tg3* priv; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ tg3_writephy (struct tg3*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tg3_mdio_write(struct mii_bus *bp, int mii_id, int reg, u16 val)
{
	struct tg3 *tp = bp->priv;
	u32 ret = 0;

	spin_lock_bh(&tp->lock);

	if (tg3_writephy(tp, reg, val))
		ret = -EIO;

	spin_unlock_bh(&tp->lock);

	return ret;
}