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
struct mb86a16_state {int dummy; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  MB86A16_ERROR ; 
 int /*<<< orphan*/  MB86A16_INFO ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int mb86a16_read (struct mb86a16_state*,int,unsigned char*) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int sync_chk(struct mb86a16_state *state,
		    unsigned char *VIRM)
{
	unsigned char val;
	int sync;

	if (mb86a16_read(state, 0x0d, &val) != 2)
		goto err;

	dprintk(verbose, MB86A16_INFO, 1, "Status = %02x,", val);
	sync = val & 0x01;
	*VIRM = (val & 0x1c) >> 2;

	return sync;
err:
	dprintk(verbose, MB86A16_ERROR, 1, "I2C transfer error");
	return -EREMOTEIO;

}