#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ rec_codec; scalar_t__ play_codec; int play_mode; int rec_mode; int /*<<< orphan*/  aec_level; } ;
typedef  TYPE_1__ IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  AEC_OFF ; 
 scalar_t__ G729 ; 
 scalar_t__ G729B ; 
 int /*<<< orphan*/  ixj_WriteDSPCommand (int,TYPE_1__*) ; 

__attribute__((used)) static void aec_stop(IXJ *j)
{
	j->aec_level = AEC_OFF;
	if (j->rec_codec == G729 || j->play_codec == G729 || j->rec_codec == G729B || j->play_codec == G729B) {
		ixj_WriteDSPCommand(0xE022, j);	/* Move AEC filter buffer back */

		ixj_WriteDSPCommand(0x0700, j);
	}
	if (j->play_mode != -1 && j->rec_mode != -1)
	{
		ixj_WriteDSPCommand(0xB002, j);	/* AEC Stop */
	}
}