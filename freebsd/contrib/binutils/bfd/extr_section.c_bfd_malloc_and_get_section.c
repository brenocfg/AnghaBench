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
typedef  TYPE_1__* sec_ptr ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {scalar_t__ rawsize; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_get_section_contents (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * bfd_malloc (scalar_t__) ; 

bfd_boolean
bfd_malloc_and_get_section (bfd *abfd, sec_ptr sec, bfd_byte **buf)
{
  bfd_size_type sz = sec->rawsize ? sec->rawsize : sec->size;
  bfd_byte *p = NULL;

  *buf = p;
  if (sz == 0)
    return TRUE;

  p = bfd_malloc (sec->rawsize > sec->size ? sec->rawsize : sec->size);
  if (p == NULL)
    return FALSE;
  *buf = p;

  return bfd_get_section_contents (abfd, sec, p, 0, sz);
}