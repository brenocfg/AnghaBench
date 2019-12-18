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
struct snd_emu10k1_fx8010_code {int /*<<< orphan*/ * code; int /*<<< orphan*/  code_valid; } ;
struct snd_emu10k1 {scalar_t__ audigy; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ get_user (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_emu10k1_efx_write (struct snd_emu10k1*,int,int) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_emu10k1_code_poke(struct snd_emu10k1 *emu,
				 struct snd_emu10k1_fx8010_code *icode)
{
	u32 pc, lo, hi;

	for (pc = 0; pc < (emu->audigy ? 2*1024 : 2*512); pc += 2) {
		if (!test_bit(pc / 2, icode->code_valid))
			continue;
		if (get_user(lo, &icode->code[pc + 0]) ||
		    get_user(hi, &icode->code[pc + 1]))
			return -EFAULT;
		snd_emu10k1_efx_write(emu, pc + 0, lo);
		snd_emu10k1_efx_write(emu, pc + 1, hi);
	}
	return 0;
}