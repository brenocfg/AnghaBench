#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hdr ;
struct TYPE_4__ {int /*<<< orphan*/  e_ident; } ;
typedef  TYPE_1__ Elf32_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  ELFMAG ; 
 int /*<<< orphan*/  SELFMAG ; 
 int /*<<< orphan*/  err (int,char*) ; 
 unsigned long load_bzimage (int) ; 
 unsigned long map_elf (int,TYPE_1__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read (int,TYPE_1__*,int) ; 

__attribute__((used)) static unsigned long load_kernel(int fd)
{
	Elf32_Ehdr hdr;

	/* Read in the first few bytes. */
	if (read(fd, &hdr, sizeof(hdr)) != sizeof(hdr))
		err(1, "Reading kernel");

	/* If it's an ELF file, it starts with "\177ELF" */
	if (memcmp(hdr.e_ident, ELFMAG, SELFMAG) == 0)
		return map_elf(fd, &hdr);

	/* Otherwise we assume it's a bzImage, and try to load it. */
	return load_bzimage(fd);
}