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
typedef  unsigned long bfd_size_type ;
struct TYPE_3__ {int /*<<< orphan*/  memory; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_error_no_memory ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 void* objalloc_alloc (int /*<<< orphan*/ ,unsigned long) ; 

void *
bfd_alloc (bfd *abfd, bfd_size_type size)
{
  void *ret;

  if (size != (unsigned long) size)
    {
      bfd_set_error (bfd_error_no_memory);
      return NULL;
    }

  ret = objalloc_alloc (abfd->memory, (unsigned long) size);
  if (ret == NULL)
    bfd_set_error (bfd_error_no_memory);
  return ret;
}