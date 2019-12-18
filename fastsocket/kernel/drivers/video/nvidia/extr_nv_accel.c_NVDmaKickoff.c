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
struct nvidia_par {scalar_t__ dmaCurrent; scalar_t__ dmaPut; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_PUT (struct nvidia_par*,scalar_t__) ; 

__attribute__((used)) static void NVDmaKickoff(struct nvidia_par *par)
{
	if (par->dmaCurrent != par->dmaPut) {
		par->dmaPut = par->dmaCurrent;
		WRITE_PUT(par, par->dmaPut);
	}
}