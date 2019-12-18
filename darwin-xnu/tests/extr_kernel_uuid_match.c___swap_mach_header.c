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
struct mach_header {int /*<<< orphan*/  flags; int /*<<< orphan*/  sizeofcmds; int /*<<< orphan*/  ncmds; int /*<<< orphan*/  filetype; int /*<<< orphan*/  cpusubtype; int /*<<< orphan*/  cputype; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAP32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __swap_mach_header(struct mach_header *header) {
	SWAP32(header->magic);
	SWAP32(header->cputype);
	SWAP32(header->cpusubtype);
	SWAP32(header->filetype);
	SWAP32(header->ncmds);
	SWAP32(header->sizeofcmds);
	SWAP32(header->flags);
}