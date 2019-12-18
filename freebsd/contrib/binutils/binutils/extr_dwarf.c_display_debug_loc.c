#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dwarf_section {unsigned char* start; unsigned long size; char* name; unsigned long address; } ;
struct TYPE_2__ {unsigned int num_loc_offsets; unsigned long* loc_offsets; unsigned int pointer_size; unsigned long cu_offset; int* have_frame_base; unsigned long base_address; } ;

/* Variables and functions */
 char* _ (char*) ; 
 void* byte_get (unsigned char*,int) ; 
 TYPE_1__* debug_information ; 
 int decode_location_expression (unsigned char*,unsigned int,unsigned short,unsigned long) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_debug_info (void*) ; 
 unsigned int num_debug_info_entries ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static int
display_debug_loc (struct dwarf_section *section, void *file)
{
  unsigned char *start = section->start;
  unsigned char *section_end;
  unsigned long bytes;
  unsigned char *section_begin = start;
  unsigned int num_loc_list = 0;
  unsigned long last_offset = 0;
  unsigned int first = 0;
  unsigned int i;
  unsigned int j;
  int seen_first_offset = 0;
  int use_debug_info = 1;
  unsigned char *next;

  bytes = section->size;
  section_end = start + bytes;

  if (bytes == 0)
    {
      printf (_("\nThe %s section is empty.\n"), section->name);
      return 0;
    }

  load_debug_info (file);

  /* Check the order of location list in .debug_info section. If
     offsets of location lists are in the ascending order, we can
     use `debug_information' directly.  */
  for (i = 0; i < num_debug_info_entries; i++)
    {
      unsigned int num;

      num = debug_information [i].num_loc_offsets;
      num_loc_list += num;

      /* Check if we can use `debug_information' directly.  */
      if (use_debug_info && num != 0)
	{
	  if (!seen_first_offset)
	    {
	      /* This is the first location list.  */
	      last_offset = debug_information [i].loc_offsets [0];
	      first = i;
	      seen_first_offset = 1;
	      j = 1;
	    }
	  else
	    j = 0;

	  for (; j < num; j++)
	    {
	      if (last_offset >
		  debug_information [i].loc_offsets [j])
		{
		  use_debug_info = 0;
		  break;
		}
	      last_offset = debug_information [i].loc_offsets [j];
	    }
	}
    }

  if (!use_debug_info)
    /* FIXME: Should we handle this case?  */
    error (_("Location lists in .debug_info section aren't in ascending order!\n"));

  if (!seen_first_offset)
    error (_("No location lists in .debug_info section!\n"));

  /* DWARF sections under Mach-O have non-zero addresses.  */
  if (debug_information [first].num_loc_offsets > 0
      && debug_information [first].loc_offsets [0] != section->address)
    warn (_("Location lists in %s section start at 0x%lx\n"),
	  section->name, debug_information [first].loc_offsets [0]);

  printf (_("Contents of the %s section:\n\n"), section->name);
  printf (_("    Offset   Begin    End      Expression\n"));

  seen_first_offset = 0;
  for (i = first; i < num_debug_info_entries; i++)
    {
      unsigned long begin;
      unsigned long end;
      unsigned short length;
      unsigned long offset;
      unsigned int pointer_size;
      unsigned long cu_offset;
      unsigned long base_address;
      int need_frame_base;
      int has_frame_base;

      pointer_size = debug_information [i].pointer_size;
      cu_offset = debug_information [i].cu_offset;

      for (j = 0; j < debug_information [i].num_loc_offsets; j++)
	{
	  has_frame_base = debug_information [i].have_frame_base [j];
	  /* DWARF sections under Mach-O have non-zero addresses.  */
	  offset = debug_information [i].loc_offsets [j] - section->address; 
	  next = section_begin + offset;
	  base_address = debug_information [i].base_address;

	  if (!seen_first_offset)
	    seen_first_offset = 1;
	  else
	    {
	      if (start < next)
		warn (_("There is a hole [0x%lx - 0x%lx] in .debug_loc section.\n"),
		      (long)(start - section_begin), (long)(next - section_begin));
	      else if (start > next)
		warn (_("There is an overlap [0x%lx - 0x%lx] in .debug_loc section.\n"),
		      (long)(start - section_begin), (long)(next - section_begin));
	    }
	  start = next;

	  if (offset >= bytes)
	    {
	      warn (_("Offset 0x%lx is bigger than .debug_loc section size.\n"),
		    offset);
	      continue;
	    }

	  while (1)
	    {
	      if (start + 2 * pointer_size > section_end)
		{
		  warn (_("Location list starting at offset 0x%lx is not terminated.\n"),
			offset);
		  break;
		}

	      begin = byte_get (start, pointer_size);
	      start += pointer_size;
	      end = byte_get (start, pointer_size);
	      start += pointer_size;

	      if (begin == 0 && end == 0)
		{
		  printf (_("    %8.8lx <End of list>\n"), offset);
		  break;
		}

	      /* Check base address specifiers.  */
	      if (begin == -1UL && end != -1UL)
		{
		  base_address = end;
		  printf (_("    %8.8lx %8.8lx %8.8lx (base address)\n"),
			  offset, begin, end);
		  continue;
		}

	      if (start + 2 > section_end)
		{
		  warn (_("Location list starting at offset 0x%lx is not terminated.\n"),
			offset);
		  break;
		}

	      length = byte_get (start, 2);
	      start += 2;

	      if (start + length > section_end)
		{
		  warn (_("Location list starting at offset 0x%lx is not terminated.\n"),
			offset);
		  break;
		}

	      printf ("    %8.8lx %8.8lx %8.8lx (",
		      offset, begin + base_address, end + base_address);
	      need_frame_base = decode_location_expression (start,
							    pointer_size,
							    length,
							    cu_offset);
	      putchar (')');

	      if (need_frame_base && !has_frame_base)
		printf (_(" [without DW_AT_frame_base]"));

	      if (begin == end)
		fputs (_(" (start == end)"), stdout);
	      else if (begin > end)
		fputs (_(" (start > end)"), stdout);

	      putchar ('\n');

	      start += length;
	    }
	}
    }
  return 1;
}