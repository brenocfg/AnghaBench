#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* c; int /*<<< orphan*/  skill; int /*<<< orphan*/  filename; } ;
typedef  TYPE_3__ bot_character_t ;
struct TYPE_5__ {int /*<<< orphan*/  string; int /*<<< orphan*/  _float; int /*<<< orphan*/  integer; } ;
struct TYPE_6__ {int type; TYPE_1__ value; } ;

/* Variables and functions */
#define  CT_FLOAT 130 
#define  CT_INTEGER 129 
#define  CT_STRING 128 
 int /*<<< orphan*/  Log_Write (char*,...) ; 
 int MAX_CHARACTERISTICS ; 

void BotDumpCharacter(bot_character_t *ch)
{
	int i;

	Log_Write("%s", ch->filename);
	Log_Write("skill %d\n", ch->skill);
	Log_Write("{\n");
	for (i = 0; i < MAX_CHARACTERISTICS; i++)
	{
		switch(ch->c[i].type)
		{
			case CT_INTEGER: Log_Write(" %4d %d\n", i, ch->c[i].value.integer); break;
			case CT_FLOAT: Log_Write(" %4d %f\n", i, ch->c[i].value._float); break;
			case CT_STRING: Log_Write(" %4d %s\n", i, ch->c[i].value.string); break;
		} //end case
	} //end for
	Log_Write("}\n");
}