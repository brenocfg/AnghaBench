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
struct TYPE_3__ {size_t cts_offset; scalar_t__ cts_data; scalar_t__ cts_size; } ;
typedef  TYPE_1__ ctf_sect_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  PROT_READ ; 
 size_t _PAGEMASK ; 
 scalar_t__ mmap64 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,size_t) ; 

const void *
ctf_sect_mmap(ctf_sect_t *sp, int fd)
{
	size_t pageoff = sp->cts_offset & ~_PAGEMASK;

	caddr_t base = mmap64(NULL, sp->cts_size + pageoff, PROT_READ,
	    MAP_PRIVATE, fd, sp->cts_offset & _PAGEMASK);

	if (base != MAP_FAILED)
		sp->cts_data = base + pageoff;

	return (base);
}