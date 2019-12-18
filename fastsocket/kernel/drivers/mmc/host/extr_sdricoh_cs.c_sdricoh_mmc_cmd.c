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
struct sdricoh_host {int dummy; } ;

/* Variables and functions */
 unsigned int CMD_TIMEOUT ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  R200_CMD ; 
 int /*<<< orphan*/  R204_CMD_ARG ; 
 int /*<<< orphan*/  R21C_STATUS ; 
 int /*<<< orphan*/  R2E4_STATUS_RESP ; 
 unsigned int STATUS_CMD_FINISHED ; 
 unsigned int STATUS_CMD_TIMEOUT ; 
 unsigned int sdricoh_readl (struct sdricoh_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdricoh_writel (struct sdricoh_host*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int sdricoh_mmc_cmd(struct sdricoh_host *host, unsigned char opcode,
			   unsigned int arg)
{
	unsigned int status;
	int result = 0;
	unsigned int loop = 0;
	/* reset status reg? */
	sdricoh_writel(host, R21C_STATUS, 0x18);
	/* fill parameters */
	sdricoh_writel(host, R204_CMD_ARG, arg);
	sdricoh_writel(host, R200_CMD, (0x10000 << 8) | opcode);
	/* wait for command completion */
	if (opcode) {
		for (loop = 0; loop < CMD_TIMEOUT; loop++) {
			status = sdricoh_readl(host, R21C_STATUS);
			sdricoh_writel(host, R2E4_STATUS_RESP, status);
			if (status  & STATUS_CMD_FINISHED)
				break;
		}
		/* don't check for timeout in the loop it is not always
		   reset correctly
		*/
		if (loop == CMD_TIMEOUT || status & STATUS_CMD_TIMEOUT)
			result = -ETIMEDOUT;

	}

	return result;

}