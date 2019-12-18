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
struct si_sm_io {unsigned int addr_data; unsigned int regspacing; int regshift; } ;

/* Variables and functions */
 int inl (unsigned int) ; 

__attribute__((used)) static unsigned char port_inl(struct si_sm_io *io, unsigned int offset)
{
	unsigned int addr = io->addr_data;

	return (inl(addr + (offset * io->regspacing)) >> io->regshift) & 0xff;
}