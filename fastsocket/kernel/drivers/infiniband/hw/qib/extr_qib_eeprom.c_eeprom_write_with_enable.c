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
struct qib_devdata {int (* f_eeprom_wen ) (struct qib_devdata*,int) ;int /*<<< orphan*/  twsi_eeprom_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*) ; 
 int qib_twsi_blk_wr (struct qib_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int) ; 
 int qib_twsi_reset (struct qib_devdata*) ; 
 int stub1 (struct qib_devdata*,int) ; 
 int stub2 (struct qib_devdata*,int) ; 

__attribute__((used)) static int eeprom_write_with_enable(struct qib_devdata *dd, u8 offset,
		     const void *buf, int len)
{
	int ret, pwen;

	pwen = dd->f_eeprom_wen(dd, 1);
	ret = qib_twsi_reset(dd);
	if (ret)
		qib_dev_err(dd, "EEPROM Reset for write failed\n");
	else
		ret = qib_twsi_blk_wr(dd, dd->twsi_eeprom_dev,
				      offset, buf, len);
	dd->f_eeprom_wen(dd, pwen);
	return ret;
}