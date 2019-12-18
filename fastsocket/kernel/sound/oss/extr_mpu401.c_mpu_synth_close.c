#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mpu_config {scalar_t__ mode; scalar_t__ opened; int /*<<< orphan*/ * inputintr; } ;
struct coproc_operations {int /*<<< orphan*/  owner; int /*<<< orphan*/  devc; int /*<<< orphan*/  (* close ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {struct coproc_operations* coproc; } ;
struct TYPE_3__ {int midi_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  COPR_MIDI ; 
 struct mpu_config* dev_conf ; 
 TYPE_2__** midi_devs ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpu_cmd (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__** synth_devs ; 

__attribute__((used)) static void mpu_synth_close(int dev)
{ 
	int midi_dev;
	struct mpu_config *devc;
	struct coproc_operations *coprocessor;

	midi_dev = synth_devs[dev]->midi_dev;

	devc = &dev_conf[midi_dev];
	mpu_cmd(midi_dev, 0x15, 0);	/* Stop recording, playback and MIDI */
	mpu_cmd(midi_dev, 0x8a, 0);	/* Disable data in stopped mode */

	devc->inputintr = NULL;

	coprocessor = midi_devs[midi_dev]->coproc;
	if (coprocessor) {
		coprocessor->close(coprocessor->devc, COPR_MIDI);
		module_put(coprocessor->owner);
	}
	devc->opened = 0;
	devc->mode = 0;
}