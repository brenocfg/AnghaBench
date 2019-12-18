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
struct saa7146 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7146_MC2 ; 
 int SAA7146_MC2_UPLD_DEBI ; 
 int /*<<< orphan*/  SAA7146_PSR ; 
 int SAA7146_PSR_DEBI_S ; 
 int debiwait_maxwait ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int saaread (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wait_for_debi_done(struct saa7146 *saa)
{
	int i;

	/* wait for registers to be programmed */
	for (i = 0; i < 100000 &&
	     !(saaread(SAA7146_MC2) & SAA7146_MC2_UPLD_DEBI); i++)
		saaread(SAA7146_MC2);
	/* wait for transfer to complete */
	for (i = 0; i < 500000 &&
	     (saaread(SAA7146_PSR) & SAA7146_PSR_DEBI_S); i++)
		saaread(SAA7146_MC2);

	if (i > debiwait_maxwait)
		printk("wait-for-debi-done maxwait: %d\n",
			debiwait_maxwait = i);

	if (i == 500000)
		return -1;

	return 0;
}