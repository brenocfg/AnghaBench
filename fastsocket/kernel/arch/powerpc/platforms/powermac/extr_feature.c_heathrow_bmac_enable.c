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
struct macio_chip {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 long ENODEV ; 
 int /*<<< orphan*/  HEATHROW_FCR ; 
 int /*<<< orphan*/  HRW_BMAC_IO_ENABLE ; 
 int /*<<< orphan*/  HRW_BMAC_RESET ; 
 int /*<<< orphan*/  LOCK (unsigned long) ; 
 int /*<<< orphan*/  MACIO_BIC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACIO_BIS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACIO_IN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK (unsigned long) ; 
 struct macio_chip* macio_find (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static long heathrow_bmac_enable(struct device_node *node, long param,
				 long value)
{
	struct macio_chip*	macio;
	unsigned long		flags;

	macio = macio_find(node, 0);
	if (!macio)
		return -ENODEV;
	if (value) {
		LOCK(flags);
		MACIO_BIS(HEATHROW_FCR, HRW_BMAC_IO_ENABLE);
		MACIO_BIS(HEATHROW_FCR, HRW_BMAC_RESET);
		UNLOCK(flags);
		(void)MACIO_IN32(HEATHROW_FCR);
		mdelay(10);
		LOCK(flags);
		MACIO_BIC(HEATHROW_FCR, HRW_BMAC_RESET);
		UNLOCK(flags);
		(void)MACIO_IN32(HEATHROW_FCR);
		mdelay(10);
	} else {
		LOCK(flags);
		MACIO_BIC(HEATHROW_FCR, HRW_BMAC_IO_ENABLE);
		UNLOCK(flags);
	}
	return 0;
}