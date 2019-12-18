#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nvbios_init {int /*<<< orphan*/  bios; } ;
struct TYPE_2__ {scalar_t__ card_type; } ;

/* Variables and functions */
 scalar_t__ NV_50 ; 
 int init_crtc (struct nvbios_init*) ; 
 int init_link (struct nvbios_init*) ; 
 int init_or (struct nvbios_init*) ; 
 TYPE_1__* nv_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int) ; 

__attribute__((used)) static inline u32
init_nvreg(struct nvbios_init *init, u32 reg)
{
	/* C51 (at least) sometimes has the lower bits set which the VBIOS
	 * interprets to mean that access needs to go through certain IO
	 * ports instead.  The NVIDIA binary driver has been seen to access
	 * these through the NV register address, so lets assume we can
	 * do the same
	 */
	reg &= ~0x00000003;

	/* GF8+ display scripts need register addresses mangled a bit to
	 * select a specific CRTC/OR
	 */
	if (nv_device(init->bios)->card_type >= NV_50) {
		if (reg & 0x80000000) {
			reg += init_crtc(init) * 0x800;
			reg &= ~0x80000000;
		}

		if (reg & 0x40000000) {
			reg += init_or(init) * 0x800;
			reg &= ~0x40000000;
			if (reg & 0x20000000) {
				reg += init_link(init) * 0x80;
				reg &= ~0x20000000;
			}
		}
	}

	if (reg & ~0x00fffffc)
		warn("unknown bits in register 0x%08x\n", reg);
	return reg;
}