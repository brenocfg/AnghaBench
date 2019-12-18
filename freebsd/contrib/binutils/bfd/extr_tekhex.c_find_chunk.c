#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct data_struct {scalar_t__ vma; struct data_struct* next; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_size_type ;
struct TYPE_7__ {TYPE_1__* tekhex_data; } ;
struct TYPE_8__ {TYPE_2__ tdata; } ;
typedef  TYPE_3__ bfd ;
struct TYPE_6__ {struct data_struct* data; } ;

/* Variables and functions */
 scalar_t__ CHUNK_MASK ; 
 struct data_struct* bfd_zalloc (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct data_struct *
find_chunk (bfd *abfd, bfd_vma vma)
{
  struct data_struct *d = abfd->tdata.tekhex_data->data;

  vma &= ~CHUNK_MASK;
  while (d && (d->vma) != vma)
    d = d->next;

  if (!d)
    {
      /* No chunk for this address, so make one up.  */
      d = bfd_zalloc (abfd, (bfd_size_type) sizeof (struct data_struct));

      if (!d)
	return NULL;

      d->next = abfd->tdata.tekhex_data->data;
      d->vma = vma;
      abfd->tdata.tekhex_data->data = d;
    }
  return d;
}