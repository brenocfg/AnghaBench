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
struct imstt_par {scalar_t__ ramdac; int* cmap_regs; } ;

/* Variables and functions */
 int BPP16 ; 
 scalar_t__ IBM ; 
 size_t PIDXDATA ; 
 size_t PIDXHI ; 
 size_t PIDXLO ; 
 size_t TVPADDRW ; 
 size_t TVPIDATA ; 
 int TVPIRTCC ; 
 int /*<<< orphan*/  eieio () ; 

__attribute__((used)) static inline void
set_565 (struct imstt_par *par)
{
	if (par->ramdac == IBM) {
		par->cmap_regs[PIDXHI] = 0;		eieio();
		par->cmap_regs[PIDXLO] = BPP16;		eieio();
		par->cmap_regs[PIDXDATA] = 0x03;	eieio();
	} else {
		par->cmap_regs[TVPADDRW] = TVPIRTCC;	eieio();
		par->cmap_regs[TVPIDATA] = 0x45;	eieio();
	}
}