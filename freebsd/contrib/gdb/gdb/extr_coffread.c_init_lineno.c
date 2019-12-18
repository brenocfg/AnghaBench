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
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int bfd_bread (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_linetab () ; 
 char* linetab ; 
 long linetab_offset ; 
 int linetab_size ; 
 scalar_t__ local_linesz ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ xmalloc (scalar_t__) ; 

__attribute__((used)) static int
init_lineno (bfd *abfd, long offset, int size)
{
  int val;

  linetab_offset = offset;
  linetab_size = size;

  free_linetab ();

  if (size == 0)
    return 0;

  if (bfd_seek (abfd, offset, 0) < 0)
    return -1;

  /* Allocate the desired table, plus a sentinel */
  linetab = (char *) xmalloc (size + local_linesz);

  val = bfd_bread (linetab, size, abfd);
  if (val != size)
    return -1;

  /* Terminate it with an all-zero sentinel record */
  memset (linetab + size, 0, local_linesz);

  return 0;
}