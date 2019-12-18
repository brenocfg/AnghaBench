#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct load_command {scalar_t__ cmd; scalar_t__ cmdsize; } ;
struct TYPE_3__ {unsigned long ncmds; } ;
typedef  TYPE_1__ kernel_mach_header_t ;

/* Variables and functions */

void *
getcommandfromheader(kernel_mach_header_t *mhp, uint32_t cmd) {
	struct load_command *lcp;
	unsigned long i;

	lcp = (struct load_command *) (mhp + 1);
	for(i = 0; i < mhp->ncmds; i++){
		if(lcp->cmd == cmd) {
			return (void *)lcp;
		}

		lcp = (struct load_command *)((uintptr_t)lcp + lcp->cmdsize);
	}

	return NULL;
}