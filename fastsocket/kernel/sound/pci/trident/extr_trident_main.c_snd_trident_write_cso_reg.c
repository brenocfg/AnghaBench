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
struct snd_trident_voice {unsigned int CSO; int Delta; int /*<<< orphan*/  number; } ;
struct snd_trident {scalar_t__ device; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_DX_CSO_ALPHA_FMS ; 
 int /*<<< orphan*/  CH_NX_DELTA_CSO ; 
 int /*<<< orphan*/  T4D_LFO_GC_CIR ; 
 scalar_t__ TRIDENT_DEVICE_ID_NX ; 
 scalar_t__ TRID_REG (struct snd_trident*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned int,scalar_t__) ; 

__attribute__((used)) static void snd_trident_write_cso_reg(struct snd_trident * trident,
				      struct snd_trident_voice * voice,
				      unsigned int CSO)
{
	voice->CSO = CSO;
	outb(voice->number, TRID_REG(trident, T4D_LFO_GC_CIR));
	if (trident->device != TRIDENT_DEVICE_ID_NX) {
		outw(voice->CSO, TRID_REG(trident, CH_DX_CSO_ALPHA_FMS) + 2);
	} else {
		outl((voice->Delta << 24) |
		     (voice->CSO & 0x00ffffff), TRID_REG(trident, CH_NX_DELTA_CSO));
	}
}