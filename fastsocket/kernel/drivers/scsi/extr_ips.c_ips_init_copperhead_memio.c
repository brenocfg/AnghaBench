#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {scalar_t__ mem_ptr; TYPE_3__* pcidev; } ;
typedef  TYPE_1__ ips_ha_t ;
struct TYPE_5__ {scalar_t__ revision; } ;

/* Variables and functions */
 int IPS_BIT_EBM ; 
 int IPS_BIT_EI ; 
 int IPS_BIT_GHI ; 
 int IPS_BIT_OP ; 
 int IPS_GOOD_POST_STATUS ; 
 int IPS_MAX_CONFIG_BYTES ; 
 int IPS_MAX_POST_BYTES ; 
 int /*<<< orphan*/  IPS_ONE_SEC ; 
 int /*<<< orphan*/  IPS_PRINTK (int /*<<< orphan*/ ,TYPE_3__*,char*,int,int) ; 
 scalar_t__ IPS_REG_CBSP ; 
 scalar_t__ IPS_REG_CCCR ; 
 scalar_t__ IPS_REG_HISR ; 
 scalar_t__ IPS_REG_ISPR ; 
 scalar_t__ IPS_REG_NDAE ; 
 scalar_t__ IPS_REG_SCPR ; 
 scalar_t__ IPS_REVID_TROMBONE64 ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  MDELAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int
ips_init_copperhead_memio(ips_ha_t * ha)
{
	uint8_t Isr = 0;
	uint8_t Cbsp;
	uint8_t PostByte[IPS_MAX_POST_BYTES];
	uint8_t ConfigByte[IPS_MAX_CONFIG_BYTES];
	int i, j;

	METHOD_TRACE("ips_init_copperhead_memio", 1);

	for (i = 0; i < IPS_MAX_POST_BYTES; i++) {
		for (j = 0; j < 45; j++) {
			Isr = readb(ha->mem_ptr + IPS_REG_HISR);
			if (Isr & IPS_BIT_GHI)
				break;

			/* Delay for 1 Second */
			MDELAY(IPS_ONE_SEC);
		}

		if (j >= 45)
			/* error occurred */
			return (0);

		PostByte[i] = readb(ha->mem_ptr + IPS_REG_ISPR);
		writeb(Isr, ha->mem_ptr + IPS_REG_HISR);
	}

	if (PostByte[0] < IPS_GOOD_POST_STATUS) {
		IPS_PRINTK(KERN_WARNING, ha->pcidev,
			   "reset controller fails (post status %x %x).\n",
			   PostByte[0], PostByte[1]);

		return (0);
	}

	for (i = 0; i < IPS_MAX_CONFIG_BYTES; i++) {
		for (j = 0; j < 240; j++) {
			Isr = readb(ha->mem_ptr + IPS_REG_HISR);
			if (Isr & IPS_BIT_GHI)
				break;

			/* Delay for 1 Second */
			MDELAY(IPS_ONE_SEC);
		}

		if (j >= 240)
			/* error occurred */
			return (0);

		ConfigByte[i] = readb(ha->mem_ptr + IPS_REG_ISPR);
		writeb(Isr, ha->mem_ptr + IPS_REG_HISR);
	}

	for (i = 0; i < 240; i++) {
		Cbsp = readb(ha->mem_ptr + IPS_REG_CBSP);

		if ((Cbsp & IPS_BIT_OP) == 0)
			break;

		/* Delay for 1 Second */
		MDELAY(IPS_ONE_SEC);
	}

	if (i >= 240)
		/* error occurred */
		return (0);

	/* setup CCCR */
	writel(0x1010, ha->mem_ptr + IPS_REG_CCCR);

	/* Enable busmastering */
	writeb(IPS_BIT_EBM, ha->mem_ptr + IPS_REG_SCPR);

	if (ha->pcidev->revision == IPS_REVID_TROMBONE64)
		/* fix for anaconda64 */
		writel(0, ha->mem_ptr + IPS_REG_NDAE);

	/* Enable interrupts */
	writeb(IPS_BIT_EI, ha->mem_ptr + IPS_REG_HISR);

	/* if we get here then everything went OK */
	return (1);
}