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
struct sbi_instrument {int* operators; } ;
struct physical_voice_info {scalar_t__ voice_mode; } ;
struct TYPE_4__ {int nr_voice; size_t* lv_map; TYPE_1__* voc; struct sbi_instrument* i_map; struct sbi_instrument** act_i; } ;
struct TYPE_3__ {int mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int OFFS_4OP ; 
 int /*<<< orphan*/  SET_VIBRATO (int) ; 
 TYPE_2__* devc ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 struct physical_voice_info* pv_map ; 

__attribute__((used)) static void opl3_aftertouch(int dev, int voice, int pressure)
{
	int tmp;
	struct sbi_instrument *instr;
	struct physical_voice_info *map;

	if (voice < 0 || voice >= devc->nr_voice)
		return;

	map = &pv_map[devc->lv_map[voice]];

	DEB(printk("Aftertouch %d\n", voice));

	if (map->voice_mode == 0)
		return;

	/*
	 * Adjust the amount of vibrato depending the pressure
	 */

	instr = devc->act_i[voice];

	if (!instr)
		instr = &devc->i_map[0];

	if (devc->voc[voice].mode == 4)
	{
		int connection = ((instr->operators[10] & 0x01) << 1) | (instr->operators[10 + OFFS_4OP] & 0x01);

		switch (connection)
		{
			case 0:
				SET_VIBRATO(4);
				break;

			case 1:
				SET_VIBRATO(2);
				SET_VIBRATO(4);
				break;

			case 2:
				SET_VIBRATO(1);
				SET_VIBRATO(4);
				break;

			case 3:
				SET_VIBRATO(1);
				SET_VIBRATO(3);
				SET_VIBRATO(4);
				break;

		}
		/*
		 * Not implemented yet
		 */
	}
	else
	{
		SET_VIBRATO(1);

		if ((instr->operators[10] & 0x01))	/*
							 * Additive synthesis
							 */
			SET_VIBRATO(2);
	}
}