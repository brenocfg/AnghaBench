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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int MTUINDEX (int) ; 
 int MTUVALUE (int) ; 
 int /*<<< orphan*/  MTUVALUE_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTUWIDTH_GET (int /*<<< orphan*/ ) ; 
 int NMTUS ; 
 int /*<<< orphan*/  TP_MTU_TABLE ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

void t4_read_mtu_tbl(struct adapter *adap, u16 *mtus, u8 *mtu_log)
{
	u32 v;
	int i;

	for (i = 0; i < NMTUS; ++i) {
		t4_write_reg(adap, TP_MTU_TABLE,
			     MTUINDEX(0xff) | MTUVALUE(i));
		v = t4_read_reg(adap, TP_MTU_TABLE);
		mtus[i] = MTUVALUE_GET(v);
		if (mtu_log)
			mtu_log[i] = MTUWIDTH_GET(v);
	}
}