#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pattern {int* seq; int /*<<< orphan*/ ** siz; int /*<<< orphan*/ ** data; } ;
struct TYPE_3__ {scalar_t__ expires; } ;
struct dsp_tone {int index; TYPE_1__ tl; int /*<<< orphan*/  tone; scalar_t__ pattern; } ;
struct dsp {struct dsp_tone tone; } ;

/* Variables and functions */
 int /*<<< orphan*/ * DATA_S ; 
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  dsp_tone_hw_message (struct dsp*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 

void
dsp_tone_timeout(void *arg)
{
	struct dsp *dsp = arg;
	struct dsp_tone *tone = &dsp->tone;
	struct pattern *pat = (struct pattern *)tone->pattern;
	int index = tone->index;

	if (!tone->tone)
		return;

	index++;
	if (!pat->seq[index])
		index = 0;
	tone->index = index;

	/* set next tone */
	if (pat->data[index] == DATA_S)
		dsp_tone_hw_message(dsp, NULL, 0);
	else
		dsp_tone_hw_message(dsp, pat->data[index], *(pat->siz[index]));
	/* set timer */
	init_timer(&tone->tl);
	tone->tl.expires = jiffies + (pat->seq[index] * HZ) / 8000;
	add_timer(&tone->tl);
}