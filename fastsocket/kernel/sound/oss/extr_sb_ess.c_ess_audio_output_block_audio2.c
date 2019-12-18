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
struct TYPE_7__ {int intr_active_16; int /*<<< orphan*/  irq_mode_16; } ;
typedef  TYPE_2__ sb_devc ;
struct TYPE_8__ {TYPE_1__* dmap_out; TYPE_2__* devc; } ;
struct TYPE_6__ {int dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMODE_OUTPUT ; 
 TYPE_5__** audio_devs ; 
 int /*<<< orphan*/  ess_chgmixer (TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  ess_setmixer (TYPE_2__*,int,unsigned char) ; 

__attribute__((used)) static void ess_audio_output_block_audio2
	(int dev, unsigned long buf, int nr_bytes, int intrflag)
{
	int count = nr_bytes;
	sb_devc *devc = audio_devs[dev]->devc;
	short c = -nr_bytes;

	if (audio_devs[dev]->dmap_out->dma > 3) count >>= 1;
	count--;

	ess_setmixer (devc, 0x74, (unsigned char) ((unsigned short) c & 0xff));
	ess_setmixer (devc, 0x76, (unsigned char) (((unsigned short) c >> 8) & 0xff));
	ess_chgmixer (devc, 0x78, 0x03, 0x03);   /* Go */

	devc->irq_mode_16 = IMODE_OUTPUT;
		devc->intr_active_16 = 1;
}