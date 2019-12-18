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
struct snd_emu10k1_fx8010_code {int /*<<< orphan*/ * tram_addr_map; int /*<<< orphan*/ * tram_data_map; int /*<<< orphan*/  tram_valid; } ;
struct snd_emu10k1 {scalar_t__ audigy; } ;

/* Variables and functions */
 scalar_t__ A_TANKMEMCTLREGBASE ; 
 int EFAULT ; 
 scalar_t__ TANKMEMADDRREGBASE ; 
 scalar_t__ TANKMEMDATAREGBASE ; 
 scalar_t__ get_user (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_emu10k1_tram_poke(struct snd_emu10k1 *emu,
				 struct snd_emu10k1_fx8010_code *icode)
{
	int tram;
	u32 addr, val;

	for (tram = 0; tram < (emu->audigy ? 0x100 : 0xa0); tram++) {
		if (!test_bit(tram, icode->tram_valid))
			continue;
		if (get_user(val, &icode->tram_data_map[tram]) ||
		    get_user(addr, &icode->tram_addr_map[tram]))
			return -EFAULT;
		snd_emu10k1_ptr_write(emu, TANKMEMDATAREGBASE + tram, 0, val);
		if (!emu->audigy) {
			snd_emu10k1_ptr_write(emu, TANKMEMADDRREGBASE + tram, 0, addr);
		} else {
			snd_emu10k1_ptr_write(emu, TANKMEMADDRREGBASE + tram, 0, addr << 12);
			snd_emu10k1_ptr_write(emu, A_TANKMEMCTLREGBASE + tram, 0, addr >> 20);
		}
	}
	return 0;
}