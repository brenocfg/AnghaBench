#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_8__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int channels; scalar_t__ trigger_bits; } ;
typedef  TYPE_1__ sb_devc ;
struct TYPE_10__ {TYPE_1__* devc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSP_CMD_SPKON ; 
 TYPE_8__** audio_devs ; 
 int /*<<< orphan*/  ess_change (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  ess_exec_commands (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ess_out_cmds ; 
 int /*<<< orphan*/  ess_speed (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ess_write (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  sb_dsp_command (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_dsp_reset (TYPE_1__*) ; 

__attribute__((used)) static int ess_audio_prepare_for_output_audio1 (int dev, int bsize, int bcount)
{
	sb_devc *devc = audio_devs[dev]->devc;

	sb_dsp_reset(devc);
	ess_speed(devc, 1);
	ess_write (devc, 0xb8, 4);	/* Auto init DMA mode */
	ess_change (devc, 0xa8, 0x03, 3 - devc->channels);	/* Mono/stereo */
	ess_write (devc, 0xb9, 2);	/* Demand mode (4 bytes/request) */

	ess_exec_commands (devc, ess_out_cmds);

	ess_change (devc, 0xb1, 0xf0, 0x50);	/* Enable DMA */
	ess_change (devc, 0xb2, 0xf0, 0x50);	/* Enable IRQ */

	sb_dsp_command(devc, DSP_CMD_SPKON);	/* There be sound! */

	devc->trigger_bits = 0;
	return 0;
}