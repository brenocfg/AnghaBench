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
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int core_lwpid; int core_pid; } ;

/* Variables and functions */
 TYPE_1__* elf_tdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
elfcore_make_pid (bfd *abfd)
{
  return ((elf_tdata (abfd)->core_lwpid << 16)
	  + (elf_tdata (abfd)->core_pid));
}