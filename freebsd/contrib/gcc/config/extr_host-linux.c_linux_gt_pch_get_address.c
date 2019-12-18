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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAP_ANON ; 
 scalar_t__ MAP_FAILED ; 
 int MAP_PRIVATE ; 
 int PROT_NONE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 scalar_t__ TRY_EMPTY_VM_SPACE ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 size_t fread (char*,int,int,int /*<<< orphan*/ *) ; 
 void* mmap (void*,size_t,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (void*,size_t) ; 

__attribute__((used)) static void *
linux_gt_pch_get_address (size_t size, int fd)
{
  size_t buffer_size = 32 * 1024 * 1024;
  void *addr, *buffer;
  FILE *f;
  bool randomize_on;

  addr = mmap ((void *)TRY_EMPTY_VM_SPACE, size, PROT_READ | PROT_WRITE,
	       MAP_PRIVATE, fd, 0);

  /* If we failed the map, that means there's *no* free space.  */
  if (addr == (void *) MAP_FAILED)
    return NULL;
  /* Unmap the area before returning.  */
  munmap (addr, size);

  /* If we got the exact area we requested, then that's great.  */
  if (TRY_EMPTY_VM_SPACE && addr == (void *) TRY_EMPTY_VM_SPACE)
    return addr;

  /* If we didn't, then we need to look to see if virtual address
     randomization is on.  That is recorded in
     kernel.randomize_va_space.  An older implementation used
     kernel.exec-shield-randomize.  */
  f = fopen ("/proc/sys/kernel/randomize_va_space", "r");
  if (f == NULL)
    f = fopen ("/proc/sys/kernel/exec-shield-randomize", "r");
  randomize_on = false;
  if (f != NULL)
    {
      char buf[100];
      size_t c;

      c = fread (buf, 1, sizeof buf - 1, f);
      if (c > 0)
	{
	  buf[c] = '\0';
	  randomize_on = (atoi (buf) > 0);
	}
      fclose (f);
    }

  /* If it isn't, then accept the address that mmap selected as fine.  */
  if (!randomize_on)
    return addr;

  /* Otherwise, we need to try again with buffer space.  */
  buffer = mmap (0, buffer_size, PROT_NONE, MAP_PRIVATE | MAP_ANON, -1, 0);
  addr = mmap (0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
  if (buffer != (void *) MAP_FAILED)
    munmap (buffer, buffer_size);
  if (addr == (void *) MAP_FAILED)
    return NULL;
  munmap (addr, size);

  return addr;
}