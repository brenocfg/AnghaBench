#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int type; } ;
typedef  TYPE_1__ tdata_type ;
struct TYPE_6__ {unsigned int size; scalar_t__ where; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ srec_data_list_type ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int Chunk ; 
 int /*<<< orphan*/  FALSE ; 
 int MAXCHUNK ; 
 int /*<<< orphan*/  TRUE ; 
 unsigned int bfd_octets_per_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srec_write_record (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
srec_write_section (bfd *abfd,
		    tdata_type *tdata,
		    srec_data_list_type *list)
{
  unsigned int octets_written = 0;
  bfd_byte *location = list->data;

  /* Validate number of data bytes to write.  The srec length byte
     counts the address, data and crc bytes.  S1 (tdata->type == 1)
     records have two address bytes, S2 (tdata->type == 2) records
     have three, and S3 (tdata->type == 3) records have four.
     The total length can't exceed 255, and a zero data length will
     spin for a long time.  */
  if (Chunk == 0)
    Chunk = 1;
  else if (Chunk > MAXCHUNK - tdata->type - 2)
    Chunk = MAXCHUNK - tdata->type - 2;

  while (octets_written < list->size)
    {
      bfd_vma address;
      unsigned int octets_this_chunk = list->size - octets_written;

      if (octets_this_chunk > Chunk)
	octets_this_chunk = Chunk;

      address = list->where + octets_written / bfd_octets_per_byte (abfd);

      if (! srec_write_record (abfd,
			       tdata->type,
			       address,
			       location,
			       location + octets_this_chunk))
	return FALSE;

      octets_written += octets_this_chunk;
      location += octets_this_chunk;
    }

  return TRUE;
}