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
 int /*<<< orphan*/  IBM_MP2_CMD_DATA ; 
 int /*<<< orphan*/  IBM_MP2_CMD_STAT ; 
 int /*<<< orphan*/  IBM_MP2_COMMAND ; 
 int /*<<< orphan*/  debNormal ; 
 int debiread (struct saa7146*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  debiwrite (struct saa7146*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  schedule () ; 

__attribute__((used)) static int ibm_send_command(struct saa7146 *saa,
			    int command, int data, int chain)
{
	int i;

	if (chain)
		debiwrite(saa, debNormal, IBM_MP2_COMMAND, (command << 1)| 1,2);
	else
		debiwrite(saa, debNormal, IBM_MP2_COMMAND, command << 1, 2);
	debiwrite(saa, debNormal, IBM_MP2_CMD_DATA, data, 2);
	debiwrite(saa, debNormal, IBM_MP2_CMD_STAT, 1, 2);
	for (i = 0; i < 100 &&
	     (debiread(saa, debNormal, IBM_MP2_CMD_STAT, 2) & 1); i++)
		schedule();
	if (i == 100)
		return -1;
	return 0;
}