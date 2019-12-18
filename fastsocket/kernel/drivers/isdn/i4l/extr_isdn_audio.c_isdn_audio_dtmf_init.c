#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char last; scalar_t__ idx; } ;
typedef  TYPE_1__ dtmf_state ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 TYPE_1__* kmalloc (int,int /*<<< orphan*/ ) ; 

dtmf_state *
isdn_audio_dtmf_init(dtmf_state * s)
{
	if (!s)
		s = kmalloc(sizeof(dtmf_state), GFP_ATOMIC);
	if (s) {
		s->idx = 0;
		s->last = ' ';
	}
	return s;
}