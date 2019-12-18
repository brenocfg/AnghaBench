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
typedef  int u32 ;
struct saa7146 {int /*<<< orphan*/  dmadebi; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA7146_DEBI_AD ; 
 int /*<<< orphan*/  SAA7146_DEBI_COMMAND ; 
 int /*<<< orphan*/  SAA7146_DEBI_CONFIG ; 
 int /*<<< orphan*/  SAA7146_MC2 ; 
 int SAA7146_MC2_UPLD_DEBI ; 
 int /*<<< orphan*/  saawrite (int,int /*<<< orphan*/ ) ; 
 int virt_to_bus (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for_debi_done (struct saa7146*) ; 

__attribute__((used)) static int debiwrite(struct saa7146 *saa, u32 config, int addr,
	u32 val, int count)
{
	u32 cmd;
	if (count <= 0 || count > 32764)
		return -1;
	if (wait_for_debi_done(saa) < 0)
		return -1;
	saawrite(config, SAA7146_DEBI_CONFIG);
	if (count <= 4)		/* immediate transfer */
		saawrite(val, SAA7146_DEBI_AD);
	else			/* block transfer */
		saawrite(virt_to_bus(saa->dmadebi), SAA7146_DEBI_AD);
	saawrite((cmd = (count << 17) | (addr & 0xffff)), SAA7146_DEBI_COMMAND);
	saawrite((SAA7146_MC2_UPLD_DEBI << 16) | SAA7146_MC2_UPLD_DEBI,
		 SAA7146_MC2);
	return 0;
}