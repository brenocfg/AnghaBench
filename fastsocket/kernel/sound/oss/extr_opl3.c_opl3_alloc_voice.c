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
struct voice_alloc_info {scalar_t__* map; int* alloc_times; } ;
struct sbi_instrument {scalar_t__ channel; scalar_t__ key; } ;
struct TYPE_4__ {int nr_voice; struct sbi_instrument* i_map; TYPE_1__* chn_info; } ;
struct TYPE_3__ {int pgm_num; } ;

/* Variables and functions */
 scalar_t__ OPL3_PATCH ; 
 TYPE_2__* devc ; 

__attribute__((used)) static int opl3_alloc_voice(int dev, int chn, int note, struct voice_alloc_info *alloc)
{
	int i, p, best, first, avail, best_time = 0x7fffffff;
	struct sbi_instrument *instr;
	int is4op;
	int instr_no;

	if (chn < 0 || chn > 15)
		instr_no = 0;
	else
		instr_no = devc->chn_info[chn].pgm_num;

	instr = &devc->i_map[instr_no];
	if (instr->channel < 0 ||	/* Instrument not loaded */
		devc->nr_voice != 12)	/* Not in 4 OP mode */
		is4op = 0;
	else if (devc->nr_voice == 12)	/* 4 OP mode */
		is4op = (instr->key == OPL3_PATCH);
	else
		is4op = 0;

	if (is4op)
	{
		first = p = 0;
		avail = 6;
	}
	else
	{
		if (devc->nr_voice == 12)	/* 4 OP mode. Use the '2 OP only' operators first */
			first = p = 6;
		else
			first = p = 0;
		avail = devc->nr_voice;
	}

	/*
	 *    Now try to find a free voice
	 */
	best = first;

	for (i = 0; i < avail; i++)
	{
		if (alloc->map[p] == 0)
		{
			return p;
		}
		if (alloc->alloc_times[p] < best_time)		/* Find oldest playing note */
		{
			best_time = alloc->alloc_times[p];
			best = p;
		}
		p = (p + 1) % avail;
	}

	/*
	 *    Insert some kind of priority mechanism here.
	 */

	if (best < 0)
		best = 0;
	if (best > devc->nr_voice)
		best -= devc->nr_voice;

	return best;	/* All devc->voc in use. Select the first one. */
}