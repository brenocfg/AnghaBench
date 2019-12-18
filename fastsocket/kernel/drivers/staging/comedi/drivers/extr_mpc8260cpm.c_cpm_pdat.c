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
struct TYPE_2__ {unsigned long iop_pdata; unsigned long iop_pdatb; unsigned long iop_pdatc; unsigned long iop_pdatd; } ;

/* Variables and functions */
 TYPE_1__* io ; 

__attribute__((used)) static unsigned long *cpm_pdat(int port)
{
	switch (port) {
	case 0:
		return &io->iop_pdata;
	case 1:
		return &io->iop_pdatb;
	case 2:
		return &io->iop_pdatc;
	case 3:
		return &io->iop_pdatd;
	}
}