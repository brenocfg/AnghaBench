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
typedef  int /*<<< orphan*/  file_ptr ;
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 void* bfd_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_bread (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
buy_and_read (bfd *abfd, file_ptr where, bfd_size_type size)
{
  void * area = bfd_alloc (abfd, size);

  if (!area)
    return (NULL);
  if (bfd_seek (abfd, where, SEEK_SET) != 0
      || bfd_bread (area, size, abfd) != size)
    return (NULL);
  return (area);
}