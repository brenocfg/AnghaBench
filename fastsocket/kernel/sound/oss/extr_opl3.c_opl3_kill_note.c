#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct physical_voice_info {scalar_t__ voice_mode; scalar_t__ voice_num; int /*<<< orphan*/  ioaddr; } ;
struct TYPE_6__ {int nr_voice; size_t* lv_map; TYPE_2__* voc; TYPE_1__* v_alloc; } ;
struct TYPE_5__ {int keyon_byte; int volume; int panning; int bender_range; scalar_t__ mode; scalar_t__ current_freq; scalar_t__ orig_freq; scalar_t__ bender; } ;
struct TYPE_4__ {scalar_t__* map; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 scalar_t__ KEYON_BLOCK ; 
 TYPE_3__* devc ; 
 int /*<<< orphan*/  opl3_command (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 struct physical_voice_info* pv_map ; 

__attribute__((used)) static int opl3_kill_note  (int devno, int voice, int note, int velocity)
{
	 struct physical_voice_info *map;

	 if (voice < 0 || voice >= devc->nr_voice)
		 return 0;

	 devc->v_alloc->map[voice] = 0;

	 map = &pv_map[devc->lv_map[voice]];
	 DEB(printk("Kill note %d\n", voice));

	 if (map->voice_mode == 0)
		 return 0;

	 opl3_command(map->ioaddr, KEYON_BLOCK + map->voice_num, devc->voc[voice].keyon_byte & ~0x20);
	 devc->voc[voice].keyon_byte = 0;
	 devc->voc[voice].bender = 0;
	 devc->voc[voice].volume = 64;
	 devc->voc[voice].panning = 0xffff;	/* Not set */
	 devc->voc[voice].bender_range = 200;
	 devc->voc[voice].orig_freq = 0;
	 devc->voc[voice].current_freq = 0;
	 devc->voc[voice].mode = 0;
	 return 0;
}