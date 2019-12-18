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
struct i2c_au1550_data {scalar_t__ psc_base; } ;
struct TYPE_2__ {int psc_smbevnt; } ;
typedef  TYPE_1__ psc_smb_t ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int PSC_SMBEVNT_AL ; 
 int PSC_SMBEVNT_AN ; 
 int PSC_SMBEVNT_DN ; 
 int /*<<< orphan*/  au_sync () ; 
 scalar_t__ wait_xfer_done (struct i2c_au1550_data*) ; 

__attribute__((used)) static int
wait_ack(struct i2c_au1550_data *adap)
{
	u32	stat;
	volatile psc_smb_t	*sp;

	if (wait_xfer_done(adap))
		return -ETIMEDOUT;

	sp = (volatile psc_smb_t *)(adap->psc_base);

	stat = sp->psc_smbevnt;
	au_sync();

	if ((stat & (PSC_SMBEVNT_DN | PSC_SMBEVNT_AN | PSC_SMBEVNT_AL)) != 0)
		return -ETIMEDOUT;

	return 0;
}