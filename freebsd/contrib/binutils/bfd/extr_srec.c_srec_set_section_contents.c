#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int type; TYPE_3__* tail; TYPE_3__* head; } ;
typedef  TYPE_2__ tdata_type ;
struct TYPE_11__ {scalar_t__ where; int size; struct TYPE_11__* next; int /*<<< orphan*/ * data; } ;
typedef  TYPE_3__ srec_data_list_type ;
typedef  TYPE_4__* sec_ptr ;
typedef  scalar_t__ file_ptr ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_9__ {TYPE_2__* srec_data; } ;
struct TYPE_13__ {TYPE_1__ tdata; } ;
typedef  TYPE_5__ bfd ;
struct TYPE_12__ {int flags; scalar_t__ lma; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ S3Forced ; 
 int SEC_ALLOC ; 
 int SEC_LOAD ; 
 int /*<<< orphan*/  TRUE ; 
 void* bfd_alloc (TYPE_5__*,int) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 

__attribute__((used)) static bfd_boolean
srec_set_section_contents (bfd *abfd,
			   sec_ptr section,
			   const void * location,
			   file_ptr offset,
			   bfd_size_type bytes_to_do)
{
  tdata_type *tdata = abfd->tdata.srec_data;
  srec_data_list_type *entry;

  entry = bfd_alloc (abfd, sizeof (* entry));
  if (entry == NULL)
    return FALSE;

  if (bytes_to_do
      && (section->flags & SEC_ALLOC)
      && (section->flags & SEC_LOAD))
    {
      bfd_byte *data;

      data = bfd_alloc (abfd, bytes_to_do);
      if (data == NULL)
	return FALSE;
      memcpy ((void *) data, location, (size_t) bytes_to_do);

      /* Ff S3Forced is TRUE then always select S3 records,
	 regardless of the siez of the addresses.  */
      if (S3Forced)
	tdata->type = 3;
      else if ((section->lma + offset + bytes_to_do - 1) <= 0xffff)
	;  /* The default, S1, is OK.  */
      else if ((section->lma + offset + bytes_to_do - 1) <= 0xffffff
	       && tdata->type <= 2)
	tdata->type = 2;
      else
	tdata->type = 3;

      entry->data = data;
      entry->where = section->lma + offset;
      entry->size = bytes_to_do;

      /* Sort the records by address.  Optimize for the common case of
	 adding a record to the end of the list.  */
      if (tdata->tail != NULL
	  && entry->where >= tdata->tail->where)
	{
	  tdata->tail->next = entry;
	  entry->next = NULL;
	  tdata->tail = entry;
	}
      else
	{
	  srec_data_list_type **look;

	  for (look = &tdata->head;
	       *look != NULL && (*look)->where < entry->where;
	       look = &(*look)->next)
	    ;
	  entry->next = *look;
	  *look = entry;
	  if (entry->next == NULL)
	    tdata->tail = entry;
	}
    }
  return TRUE;
}