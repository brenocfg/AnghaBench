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
struct lapb_cb {unsigned short va; int mode; unsigned short vs; } ;

/* Variables and functions */
 int LAPB_EMODULUS ; 
 int LAPB_EXTENDED ; 
 int LAPB_SMODULUS ; 

int lapb_validate_nr(struct lapb_cb *lapb, unsigned short nr)
{
	unsigned short vc = lapb->va;
	int modulus;

	modulus = (lapb->mode & LAPB_EXTENDED) ? LAPB_EMODULUS : LAPB_SMODULUS;

	while (vc != lapb->vs) {
		if (nr == vc)
			return 1;
		vc = (vc + 1) % modulus;
	}

	return nr == lapb->vs;
}