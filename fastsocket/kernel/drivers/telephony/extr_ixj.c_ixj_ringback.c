#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int ringback; scalar_t__ dialtone; scalar_t__ busytone; } ;
struct TYPE_8__ {TYPE_1__ flags; } ;
typedef  TYPE_2__ IXJ ;

/* Variables and functions */
 int /*<<< orphan*/  ixj_play_tone (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ixj_set_tone_off (int,TYPE_2__*) ; 
 int /*<<< orphan*/  ixj_set_tone_on (int,TYPE_2__*) ; 

__attribute__((used)) static void ixj_ringback(IXJ *j)
{
	j->flags.busytone = 0;
	j->flags.dialtone = 0;
	j->flags.ringback = 1;
	ixj_set_tone_on(0x0FA0, j);
	ixj_set_tone_off(0x2EE0, j);
	ixj_play_tone(j, 26);
}