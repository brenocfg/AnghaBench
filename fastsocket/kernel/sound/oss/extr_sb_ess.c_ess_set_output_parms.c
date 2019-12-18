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
struct TYPE_3__ {unsigned long trg_buf_16; int trg_bytes_16; int trg_intrflag_16; unsigned long trg_buf; int trg_bytes; int trg_intrflag; void* irq_mode; void* irq_mode_16; scalar_t__ duplex; } ;
typedef  TYPE_1__ sb_devc ;
struct TYPE_4__ {TYPE_1__* devc; } ;

/* Variables and functions */
 void* IMODE_OUTPUT ; 
 TYPE_2__** audio_devs ; 

__attribute__((used)) static void ess_set_output_parms
	(int dev, unsigned long buf, int nr_bytes, int intrflag)
{
	sb_devc *devc = audio_devs[dev]->devc;

	if (devc->duplex) {
		devc->trg_buf_16 = buf;
		devc->trg_bytes_16 = nr_bytes;
		devc->trg_intrflag_16 = intrflag;
		devc->irq_mode_16 = IMODE_OUTPUT;
	} else {
		devc->trg_buf = buf;
		devc->trg_bytes = nr_bytes;
		devc->trg_intrflag = intrflag;
		devc->irq_mode = IMODE_OUTPUT;
	}
}