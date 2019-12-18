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
struct pex_msdos {int /*<<< orphan*/ ** files; } ;

/* Variables and functions */
 scalar_t__ PEX_MSDOS_FD_OFFSET ; 
 int PEX_MSDOS_FILE_COUNT ; 
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static int
pex_msdos_fdindex (struct pex_msdos *ms, int fd)
{
  fd -= PEX_MSDOS_FD_OFFSET;
  if (fd < 0 || fd >= PEX_MSDOS_FILE_COUNT || ms->files[fd] == NULL)
    abort ();
  return fd;
}