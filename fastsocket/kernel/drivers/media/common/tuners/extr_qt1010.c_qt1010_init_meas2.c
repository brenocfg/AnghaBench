#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct qt1010_priv {int dummy; } ;
struct TYPE_3__ {scalar_t__ member_0; int member_1; size_t member_2; scalar_t__ oper; int /*<<< orphan*/  reg; int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ qt1010_i2c_oper_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ QT1010_RD ; 
 scalar_t__ QT1010_WR ; 
 int qt1010_readreg (struct qt1010_priv*,int /*<<< orphan*/ ,size_t*) ; 
 int qt1010_writereg (struct qt1010_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 qt1010_init_meas2(struct qt1010_priv *priv,
			    u8 reg_init_val, u8 *retval)
{
	u8 i, val;
	int err;
	qt1010_i2c_oper_t i2c_data[] = {
		{ QT1010_WR, 0x07, reg_init_val },
		{ QT1010_WR, 0x22, 0xd0 },
		{ QT1010_WR, 0x1e, 0x00 },
		{ QT1010_WR, 0x1e, 0xd0 },
		{ QT1010_RD, 0x22, 0xff },
		{ QT1010_WR, 0x1e, 0x00 },
		{ QT1010_WR, 0x22, 0xff }
	};
	for (i = 0; i < ARRAY_SIZE(i2c_data); i++) {
		if (i2c_data[i].oper == QT1010_WR) {
			err = qt1010_writereg(priv, i2c_data[i].reg,
					      i2c_data[i].val);
		} else {
			err = qt1010_readreg(priv, i2c_data[i].reg, &val);
		}
		if (err) return err;
	}
	*retval = val;
	return 0;
}