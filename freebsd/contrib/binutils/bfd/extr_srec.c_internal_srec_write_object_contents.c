#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_3__* head; } ;
typedef  TYPE_2__ tdata_type ;
struct TYPE_15__ {struct TYPE_15__* next; } ;
typedef  TYPE_3__ srec_data_list_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_13__ {TYPE_2__* srec_data; } ;
struct TYPE_16__ {TYPE_1__ tdata; } ;
typedef  TYPE_4__ bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  srec_write_header (TYPE_4__*) ; 
 int /*<<< orphan*/  srec_write_section (TYPE_4__*,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  srec_write_symbols (TYPE_4__*) ; 
 int /*<<< orphan*/  srec_write_terminator (TYPE_4__*,TYPE_2__*) ; 

__attribute__((used)) static bfd_boolean
internal_srec_write_object_contents (bfd *abfd, int symbols)
{
  tdata_type *tdata = abfd->tdata.srec_data;
  srec_data_list_type *list;

  if (symbols)
    {
      if (! srec_write_symbols (abfd))
	return FALSE;
    }

  if (! srec_write_header (abfd))
    return FALSE;

  /* Now wander though all the sections provided and output them.  */
  list = tdata->head;

  while (list != (srec_data_list_type *) NULL)
    {
      if (! srec_write_section (abfd, tdata, list))
	return FALSE;
      list = list->next;
    }
  return srec_write_terminator (abfd, tdata);
}