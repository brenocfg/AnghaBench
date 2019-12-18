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
struct sbi_instrument {scalar_t__ channel; unsigned char* operators; } ;
struct physical_voice_info {scalar_t__* op; int /*<<< orphan*/  ioaddr; } ;
struct TYPE_4__ {int nr_voice; size_t* lv_map; TYPE_1__* voc; struct sbi_instrument* i_map; struct sbi_instrument** act_i; } ;
struct TYPE_3__ {int mode; } ;

/* Variables and functions */
 scalar_t__ KSL_LEVEL ; 
 int OFFS_4OP ; 
 int /*<<< orphan*/  calc_vol (unsigned char*,int,int) ; 
 TYPE_2__* devc ; 
 int /*<<< orphan*/  opl3_command (int /*<<< orphan*/ ,scalar_t__,unsigned char) ; 
 struct physical_voice_info* pv_map ; 

__attribute__((used)) static void set_voice_volume(int voice, int volume, int main_vol)
{
	unsigned char vol1, vol2, vol3, vol4;
	struct sbi_instrument *instr;
	struct physical_voice_info *map;

	if (voice < 0 || voice >= devc->nr_voice)
		return;

	map = &pv_map[devc->lv_map[voice]];
	instr = devc->act_i[voice];

	if (!instr)
		instr = &devc->i_map[0];

	if (instr->channel < 0)
		return;

	if (devc->voc[voice].mode == 0)
		return;

	if (devc->voc[voice].mode == 2)
	{
		vol1 = instr->operators[2];
		vol2 = instr->operators[3];
		if ((instr->operators[10] & 0x01))
		{
			calc_vol(&vol1, volume, main_vol);
			calc_vol(&vol2, volume, main_vol);
		}
		else
		{
			calc_vol(&vol2, volume, main_vol);
		}
		opl3_command(map->ioaddr, KSL_LEVEL + map->op[0], vol1);
		opl3_command(map->ioaddr, KSL_LEVEL + map->op[1], vol2);
	}
	else
	{	/*
		 * 4 OP voice
		 */
		int connection;

		vol1 = instr->operators[2];
		vol2 = instr->operators[3];
		vol3 = instr->operators[OFFS_4OP + 2];
		vol4 = instr->operators[OFFS_4OP + 3];

		/*
		 * The connection method for 4 OP devc->voc is defined by the rightmost
		 * bits at the offsets 10 and 10+OFFS_4OP
		 */

		connection = ((instr->operators[10] & 0x01) << 1) | (instr->operators[10 + OFFS_4OP] & 0x01);

		switch (connection)
		{
			case 0:
				calc_vol(&vol4, volume, main_vol);
				break;

			case 1:
				calc_vol(&vol2, volume, main_vol);
				calc_vol(&vol4, volume, main_vol);
				break;

			case 2:
				calc_vol(&vol1, volume, main_vol);
				calc_vol(&vol4, volume, main_vol);
				break;

			case 3:
				calc_vol(&vol1, volume, main_vol);
				calc_vol(&vol3, volume, main_vol);
				calc_vol(&vol4, volume, main_vol);
				break;

			default:
				;
		}
		opl3_command(map->ioaddr, KSL_LEVEL + map->op[0], vol1);
		opl3_command(map->ioaddr, KSL_LEVEL + map->op[1], vol2);
		opl3_command(map->ioaddr, KSL_LEVEL + map->op[2], vol3);
		opl3_command(map->ioaddr, KSL_LEVEL + map->op[3], vol4);
	}
}