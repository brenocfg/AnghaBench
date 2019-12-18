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
typedef  int /*<<< orphan*/  pcm_t ;
struct TYPE_5__ {scalar_t__ cycles; TYPE_1__* chan; int /*<<< orphan*/  ram; int /*<<< orphan*/  bank; } ;
struct TYPE_4__ {int pan; } ;

/* Variables and functions */
 int /*<<< orphan*/ * blip ; 
 int /*<<< orphan*/  blip_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ pcm ; 

void pcm_reset(void)
{
  /* reset chip & clear external RAM */
  memset(&pcm, 0, sizeof(pcm_t));

  /* reset default bank */
  pcm.bank = pcm.ram;

  /* reset channels stereo panning */
  pcm.chan[0].pan = 0xff;
  pcm.chan[1].pan = 0xff;
  pcm.chan[2].pan = 0xff;
  pcm.chan[3].pan = 0xff;
  pcm.chan[4].pan = 0xff;
  pcm.chan[5].pan = 0xff;
  pcm.chan[6].pan = 0xff;
  pcm.chan[7].pan = 0xff;

  /* reset master clocks counter */
  pcm.cycles = 0;

  /* clear blip buffers */
  blip_clear(blip[0]);
  blip_clear(blip[1]);
}