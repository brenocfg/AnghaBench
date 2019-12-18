#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct i2c_au1550_data {int xfer_timeout; scalar_t__ psc_base; } ;
struct TYPE_2__ {int psc_smbevnt; } ;
typedef  TYPE_1__ psc_smb_t ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int PSC_SMBEVNT_MD ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
wait_master_done(struct i2c_au1550_data *adap)
{
	u32	stat;
	int	i;
	volatile psc_smb_t	*sp;

	sp = (volatile psc_smb_t *)(adap->psc_base);

	/* Wait for Master Done.
	*/
	for (i = 0; i < adap->xfer_timeout; i++) {
		stat = sp->psc_smbevnt;
		au_sync();
		if ((stat & PSC_SMBEVNT_MD) != 0)
			return 0;
		udelay(1);
	}

	return -ETIMEDOUT;
}