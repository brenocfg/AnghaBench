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
struct physical_voice_info {scalar_t__ voice_mode; scalar_t__ voice_num; int /*<<< orphan*/  ioaddr; } ;
struct TYPE_4__ {size_t* lv_map; TYPE_1__* voc; } ;
struct TYPE_3__ {int bender; int keyon_byte; int current_freq; int /*<<< orphan*/  bender_range; int /*<<< orphan*/  orig_freq; } ;

/* Variables and functions */
 scalar_t__ FNUM_LOW ; 
 scalar_t__ KEYON_BLOCK ; 
 int compute_finetune (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* devc ; 
 int /*<<< orphan*/  freq_to_fnum (int,int*,int*) ; 
 int /*<<< orphan*/  opl3_command (int /*<<< orphan*/ ,scalar_t__,unsigned char) ; 
 struct physical_voice_info* pv_map ; 

__attribute__((used)) static void bend_pitch(int dev, int voice, int value)
{
	unsigned char data;
	int block, fnum, freq;
	struct physical_voice_info *map;

	map = &pv_map[devc->lv_map[voice]];

	if (map->voice_mode == 0)
		return;

	devc->voc[voice].bender = value;
	if (!value)
		return;
	if (!(devc->voc[voice].keyon_byte & 0x20))
		return;	/*
			 * Not keyed on
			 */

	freq = compute_finetune(devc->voc[voice].orig_freq, devc->voc[voice].bender, devc->voc[voice].bender_range, 0);
	devc->voc[voice].current_freq = freq;

	freq_to_fnum(freq, &block, &fnum);

	data = fnum & 0xff;	/*
				 * Least significant bits of fnumber
				 */
	opl3_command(map->ioaddr, FNUM_LOW + map->voice_num, data);

	data = 0x20 | ((block & 0x7) << 2) | ((fnum >> 8) & 0x3);
	devc->voc[voice].keyon_byte = data;
	opl3_command(map->ioaddr, KEYON_BLOCK + map->voice_num, data);
}