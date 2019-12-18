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
struct av7110 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBINOSWAP ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dprintk (int,char*,struct av7110*) ; 
 int irdebi (struct av7110*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int waitdebi(struct av7110 *av7110, int adr, int state)
{
	int k;

	dprintk(4, "%p\n", av7110);

	for (k = 0; k < 100; k++) {
		if (irdebi(av7110, DEBINOSWAP, adr, 0, 2) == state)
			return 0;
		udelay(5);
	}
	return -ETIMEDOUT;
}