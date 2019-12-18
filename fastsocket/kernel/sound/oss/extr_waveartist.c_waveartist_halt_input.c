#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ io_base; } ;
struct TYPE_7__ {TYPE_1__ hw; int /*<<< orphan*/  audio_mode; } ;
typedef  TYPE_2__ wavnc_info ;
struct TYPE_8__ {scalar_t__ devc; } ;

/* Variables and functions */
 int IRQ_REQ ; 
 int /*<<< orphan*/  PCM_ENABLE_INPUT ; 
 scalar_t__ STATR ; 
 int /*<<< orphan*/  WACMD_INPUTSTOP ; 
 TYPE_5__** audio_devs ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  waveartist_cmd1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waveartist_iack (TYPE_2__*) ; 
 int /*<<< orphan*/  waveartist_lock ; 

__attribute__((used)) static void
waveartist_halt_input(int dev)
{
	wavnc_info	*devc = (wavnc_info *) audio_devs[dev]->devc;
	unsigned long	flags;

	spin_lock_irqsave(&waveartist_lock, flags);

	/*
	 * Stop capture
	 */
	waveartist_cmd1(devc, WACMD_INPUTSTOP);

	devc->audio_mode &= ~PCM_ENABLE_INPUT;

	/*
	 * Clear interrupt by toggling
	 * the IRQ_ACK bit in CTRL
	 */
	if (inb(devc->hw.io_base + STATR) & IRQ_REQ)
		waveartist_iack(devc);

//	devc->audio_mode &= ~PCM_ENABLE_INPUT;

	spin_unlock_irqrestore(&waveartist_lock, flags);
}