#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cs_struct ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ cs_insn ;
struct TYPE_5__ {int /*<<< orphan*/  ins; } ;

/* Variables and functions */
 TYPE_2__* OpInfoTable ; 

void MOS65XX_get_insn_id(cs_struct *h, cs_insn *insn, unsigned int id)
{
	if (id < 256) {
		insn->id = OpInfoTable[id].ins;
	}
}