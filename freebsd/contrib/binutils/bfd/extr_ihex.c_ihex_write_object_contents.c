#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ihex_data_list {scalar_t__ where; int* data; scalar_t__ size; struct ihex_data_list* next; } ;
typedef  scalar_t__ bfd_vma ;
typedef  scalar_t__ bfd_size_type ;
typedef  int bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_8__ {TYPE_1__* ihex_data; } ;
struct TYPE_9__ {scalar_t__ start_address; TYPE_2__ tdata; } ;
typedef  TYPE_3__ bfd ;
struct TYPE_7__ {struct ihex_data_list* head; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 scalar_t__ CHUNK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bfd_error_bad_value ; 
 int /*<<< orphan*/  bfd_get_filename (TYPE_3__*) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ihex_write_record (TYPE_3__*,int,unsigned int,int,int*) ; 
 int /*<<< orphan*/  sprintf_vma (char*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bfd_boolean
ihex_write_object_contents (bfd *abfd)
{
  bfd_vma segbase;
  bfd_vma extbase;
  struct ihex_data_list *l;

  segbase = 0;
  extbase = 0;
  for (l = abfd->tdata.ihex_data->head; l != NULL; l = l->next)
    {
      bfd_vma where;
      bfd_byte *p;
      bfd_size_type count;

      where = l->where;
      p = l->data;
      count = l->size;

      while (count > 0)
	{
	  size_t now;
	  unsigned int rec_addr;

	  now = count;
	  if (count > CHUNK)
	    now = CHUNK;

	  if (where > segbase + extbase + 0xffff)
	    {
	      bfd_byte addr[2];

	      /* We need a new base address.  */
	      if (where <= 0xfffff)
		{
		  /* The addresses should be sorted.  */
		  BFD_ASSERT (extbase == 0);

		  segbase = where & 0xf0000;
		  addr[0] = (bfd_byte)(segbase >> 12) & 0xff;
		  addr[1] = (bfd_byte)(segbase >> 4) & 0xff;
		  if (! ihex_write_record (abfd, 2, 0, 2, addr))
		    return FALSE;
		}
	      else
		{
		  /* The extended address record and the extended
                     linear address record are combined, at least by
                     some readers.  We need an extended linear address
                     record here, so if we've already written out an
                     extended address record, zero it out to avoid
                     confusion.  */
		  if (segbase != 0)
		    {
		      addr[0] = 0;
		      addr[1] = 0;
		      if (! ihex_write_record (abfd, 2, 0, 2, addr))
			return FALSE;
		      segbase = 0;
		    }

		  extbase = where & 0xffff0000;
		  if (where > extbase + 0xffff)
		    {
		      char buf[20];

		      sprintf_vma (buf, where);
		      (*_bfd_error_handler)
			(_("%s: address 0x%s out of range for Intel Hex file"),
			 bfd_get_filename (abfd), buf);
		      bfd_set_error (bfd_error_bad_value);
		      return FALSE;
		    }
		  addr[0] = (bfd_byte)(extbase >> 24) & 0xff;
		  addr[1] = (bfd_byte)(extbase >> 16) & 0xff;
		  if (! ihex_write_record (abfd, 2, 0, 4, addr))
		    return FALSE;
		}
	    }

	  rec_addr = where - (extbase + segbase);

          /* Output records shouldn't cross 64K boundaries.  */
          if (rec_addr + now > 0xffff)
            now = 0x10000 - rec_addr;

	  if (! ihex_write_record (abfd, now, rec_addr, 0, p))
	    return FALSE;

	  where += now;
	  p += now;
	  count -= now;
	}
    }

  if (abfd->start_address != 0)
    {
      bfd_vma start;
      bfd_byte startbuf[4];

      start = abfd->start_address;

      if (start <= 0xfffff)
	{
	  startbuf[0] = (bfd_byte)((start & 0xf0000) >> 12) & 0xff;
	  startbuf[1] = 0;
	  startbuf[2] = (bfd_byte)(start >> 8) & 0xff;
	  startbuf[3] = (bfd_byte)start & 0xff;
	  if (! ihex_write_record (abfd, 4, 0, 3, startbuf))
	    return FALSE;
	}
      else
	{
	  startbuf[0] = (bfd_byte)(start >> 24) & 0xff;
	  startbuf[1] = (bfd_byte)(start >> 16) & 0xff;
	  startbuf[2] = (bfd_byte)(start >> 8) & 0xff;
	  startbuf[3] = (bfd_byte)start & 0xff;
	  if (! ihex_write_record (abfd, 4, 0, 5, startbuf))
	    return FALSE;
	}
    }

  if (! ihex_write_record (abfd, 0, 0, 1, NULL))
    return FALSE;

  return TRUE;
}