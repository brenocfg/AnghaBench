#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ TBC; scalar_t__ TB; scalar_t__ TAC; scalar_t__ TA; scalar_t__ mode; } ;
struct TYPE_8__ {TYPE_1__ ST; } ;
struct TYPE_11__ {scalar_t__ slot_mask; TYPE_2__ OPN; } ;
struct TYPE_10__ {scalar_t__ op1_out; scalar_t__ mem_value; TYPE_3__* SLOT; scalar_t__ fc; } ;
struct TYPE_9__ {int /*<<< orphan*/  volume; int /*<<< orphan*/  state; } ;
typedef  TYPE_4__ FM_CH ;

/* Variables and functions */
 int /*<<< orphan*/  EG_OFF ; 
 int /*<<< orphan*/  MAX_ATT_INDEX ; 
 TYPE_5__ ym2612 ; 

__attribute__((used)) static void reset_channels(FM_CH *CH)
{
	int c,s;

	ym2612.OPN.ST.mode   = 0;	/* normal mode */
	ym2612.OPN.ST.TA     = 0;
	ym2612.OPN.ST.TAC    = 0;
	ym2612.OPN.ST.TB     = 0;
	ym2612.OPN.ST.TBC    = 0;

	for( c = 0 ; c < 6 ; c++ )
	{
		CH[c].fc = 0;
		for(s = 0 ; s < 4 ; s++ )
		{
			CH[c].SLOT[s].state= EG_OFF;
			CH[c].SLOT[s].volume = MAX_ATT_INDEX;
		}
		CH[c].mem_value = CH[c].op1_out = 0;
	}
	ym2612.slot_mask = 0;
}