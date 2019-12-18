#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sdio_func {unsigned char max_blksize; unsigned char enable_timeout; TYPE_2__* card; } ;
struct TYPE_3__ {unsigned int sdio_vsn; } ;
struct TYPE_4__ {TYPE_1__ cccr; } ;

/* Variables and functions */
 int EILSEQ ; 
 int EINVAL ; 
 int /*<<< orphan*/  HZ ; 
 unsigned int SDIO_SDIO_REV_1_00 ; 
 scalar_t__ cistpl_funce_whitelisted (unsigned char const) ; 
 unsigned char jiffies_to_msecs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cistpl_funce_func(struct sdio_func *func,
			     const unsigned char *buf, unsigned size)
{
	unsigned vsn;
	unsigned min_size;

	/* let SDIO drivers take care of whitelisted FUNCE tuples */
	if (cistpl_funce_whitelisted(buf[0]))
		return -EILSEQ;

	vsn = func->card->cccr.sdio_vsn;
	min_size = (vsn == SDIO_SDIO_REV_1_00) ? 28 : 42;

	if (size < min_size || buf[0] != 1)
		return -EINVAL;

	/* TPLFE_MAX_BLK_SIZE */
	func->max_blksize = buf[12] | (buf[13] << 8);

	/* TPLFE_ENABLE_TIMEOUT_VAL, present in ver 1.1 and above */
	if (vsn > SDIO_SDIO_REV_1_00)
		func->enable_timeout = (buf[28] | (buf[29] << 8)) * 10;
	else
		func->enable_timeout = jiffies_to_msecs(HZ);

	return 0;
}