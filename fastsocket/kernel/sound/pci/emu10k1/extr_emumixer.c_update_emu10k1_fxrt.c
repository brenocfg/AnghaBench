#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_emu10k1 {scalar_t__ audigy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_FXRT1 ; 
 int /*<<< orphan*/  A_FXRT2 ; 
 int /*<<< orphan*/  FXRT ; 
 int /*<<< orphan*/  snd_emu10k1_compose_audigy_fxrt1 (unsigned char*) ; 
 int /*<<< orphan*/  snd_emu10k1_compose_audigy_fxrt2 (unsigned char*) ; 
 int /*<<< orphan*/  snd_emu10k1_compose_send_routing (unsigned char*) ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_emu10k1_fxrt(struct snd_emu10k1 *emu, int voice, unsigned char *route)
{
	if (emu->audigy) {
		snd_emu10k1_ptr_write(emu, A_FXRT1, voice,
				      snd_emu10k1_compose_audigy_fxrt1(route));
		snd_emu10k1_ptr_write(emu, A_FXRT2, voice,
				      snd_emu10k1_compose_audigy_fxrt2(route));
	} else {
		snd_emu10k1_ptr_write(emu, FXRT, voice,
				      snd_emu10k1_compose_send_routing(route));
	}
}