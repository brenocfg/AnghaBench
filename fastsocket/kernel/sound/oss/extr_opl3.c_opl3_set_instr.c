#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int nr_voice; int /*<<< orphan*/ * i_map; int /*<<< orphan*/ ** act_i; } ;

/* Variables and functions */
 int SBFM_MAXINSTR ; 
 TYPE_1__* devc ; 

__attribute__((used)) static int opl3_set_instr  (int dev, int voice, int instr_no)
{
	if (voice < 0 || voice >= devc->nr_voice)
		return 0;
	if (instr_no < 0 || instr_no >= SBFM_MAXINSTR)
		instr_no = 0;	/* Acoustic piano (usually) */

	devc->act_i[voice] = &devc->i_map[instr_no];
	return 0;
}