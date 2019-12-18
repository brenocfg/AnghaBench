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
 int saaread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saawrite (int,int /*<<< orphan*/ ) ; 
 int virt_to_bus (int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for_debi_done (struct saa7146*) ; 

__attribute__((used)) static u32 debiread(struct saa7146 *saa, u32 config, int addr, int count)
{
	u32 result = 0;

	if (count > 32764 || count <= 0)
		return 0;
	if (wait_for_debi_done(saa) < 0)
		return 0;
	saawrite(virt_to_bus(saa->dmadebi), SAA7146_DEBI_AD);
	saawrite((count << 17) | 0x10000 | (addr & 0xffff),
		 SAA7146_DEBI_COMMAND);
	saawrite(config, SAA7146_DEBI_CONFIG);
	saawrite((SAA7146_MC2_UPLD_DEBI << 16) | SAA7146_MC2_UPLD_DEBI,
		 SAA7146_MC2);
	if (count > 4)		/* not an immediate transfer */
		return count;
	wait_for_debi_done(saa);
	result = saaread(SAA7146_DEBI_AD);
	if (count == 1)
		result &= 0xff;
	if (count == 2)
		result &= 0xffff;
	if (count == 3)
		result &= 0xffffff;
	return result;
}