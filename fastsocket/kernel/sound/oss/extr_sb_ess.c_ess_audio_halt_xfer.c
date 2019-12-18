#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ duplex; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ sb_devc ;
struct TYPE_6__ {TYPE_1__* devc; } ;

/* Variables and functions */
 TYPE_4__** audio_devs ; 
 int /*<<< orphan*/  ess_chgmixer (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  sb_dsp_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ess_audio_halt_xfer(int dev)
{
	unsigned long flags;
	sb_devc *devc = audio_devs[dev]->devc;

	spin_lock_irqsave(&devc->lock, flags);
	sb_dsp_reset(devc);
	spin_unlock_irqrestore(&devc->lock, flags);

	/*
	 * Audio 2 may still be operational! Creates awful sounds!
	 */
	if (devc->duplex) ess_chgmixer(devc, 0x78, 0x03, 0x00);
}