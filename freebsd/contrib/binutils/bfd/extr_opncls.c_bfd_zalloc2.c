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
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 scalar_t__ HALF_BFD_SIZE_TYPE ; 
 void* bfd_alloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  bfd_error_no_memory ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

void *
bfd_zalloc2 (bfd *abfd, bfd_size_type nmemb, bfd_size_type size)
{
  void *res;

  if ((nmemb | size) >= HALF_BFD_SIZE_TYPE
      && size != 0
      && nmemb > ~(bfd_size_type) 0 / size)
    {
      bfd_set_error (bfd_error_no_memory);
      return NULL;
    }

  size *= nmemb;

  res = bfd_alloc (abfd, size);
  if (res)
    memset (res, 0, (size_t) size);
  return res;
}