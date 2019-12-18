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

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 scalar_t__ MAP_FAILED ; 
 int MAP_FIXED ; 
 int MAP_PRIVATE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 scalar_t__ errno ; 
 size_t getpagesize () ; 
 int mincore (char*,size_t,void*) ; 
 void* mmap (void*,size_t,int,int,int,size_t) ; 
 int /*<<< orphan*/  munmap (void*,size_t) ; 

__attribute__((used)) static int
sol_gt_pch_use_address (void *base, size_t size, int fd, size_t offset)
{
  void *addr;

  /* We're called with size == 0 if we're not planning to load a PCH
     file at all.  This allows the hook to free any static space that
     we might have allocated at link time.  */
  if (size == 0)
    return -1;

  addr = mmap (base, size, PROT_READ | PROT_WRITE, MAP_PRIVATE,
	       fd, offset);

  /* Solaris isn't good about honoring the mmap START parameter
     without MAP_FIXED set.  Before we give up, search the desired
     address space with mincore to see if the space is really free.  */
  if (addr != base)
    {
      size_t page_size = getpagesize();
      char one_byte;
      size_t i;

      if (addr != (void *) MAP_FAILED)
	munmap (addr, size);

      errno = 0;
      for (i = 0; i < size; i += page_size)
	if (mincore ((char *)base + i, page_size, (void *)&one_byte) == -1
	    && errno == ENOMEM)
	  continue; /* The page is not mapped.  */
	else
	  break;

      if (i >= size)
	addr = mmap (base, size, 
		     PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_FIXED,
		     fd, offset);
    }

  return addr == base ? 1 : -1;
}