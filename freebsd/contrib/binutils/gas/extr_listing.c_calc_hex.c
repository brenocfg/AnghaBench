#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ offsetT ;
struct TYPE_4__ {TYPE_2__* frag; } ;
typedef  TYPE_1__ list_info_type ;
struct TYPE_5__ {scalar_t__ fr_fix; unsigned int fr_address; int* fr_literal; scalar_t__ fr_type; int fr_var; int fr_offset; struct TYPE_5__* fr_next; TYPE_1__* line; } ;
typedef  TYPE_2__ fragS ;

/* Variables and functions */
 int MAX_BYTES ; 
 unsigned int OCTETS_PER_BYTE ; 
 char* data_buffer ; 
 scalar_t__ rs_fill ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static unsigned int
calc_hex (list_info_type *list)
{
  int data_buffer_size;
  list_info_type *first = list;
  unsigned int address = ~(unsigned int) 0;
  fragS *frag;
  fragS *frag_ptr;
  unsigned int octet_in_frag;

  /* Find first frag which says it belongs to this line.  */
  frag = list->frag;
  while (frag && frag->line != list)
    frag = frag->fr_next;

  frag_ptr = frag;

  data_buffer_size = 0;

  /* Dump all the frags which belong to this line.  */
  while (frag_ptr != (fragS *) NULL && frag_ptr->line == first)
    {
      /* Print as many bytes from the fixed part as is sensible.  */
      octet_in_frag = 0;
      while ((offsetT) octet_in_frag < frag_ptr->fr_fix
	     && data_buffer_size < MAX_BYTES - 3)
	{
	  if (address == ~(unsigned int) 0)
	    address = frag_ptr->fr_address / OCTETS_PER_BYTE;

	  sprintf (data_buffer + data_buffer_size,
		   "%02X",
		   (frag_ptr->fr_literal[octet_in_frag]) & 0xff);
	  data_buffer_size += 2;
	  octet_in_frag++;
	}
      if (frag_ptr->fr_type == rs_fill)
	{
	  unsigned int var_rep_max = octet_in_frag;
	  unsigned int var_rep_idx = octet_in_frag;

	  /* Print as many bytes from the variable part as is sensible.  */
	  while (((offsetT) octet_in_frag
		  < (frag_ptr->fr_fix + frag_ptr->fr_var * frag_ptr->fr_offset))
		 && data_buffer_size < MAX_BYTES - 3)
	    {
	      if (address == ~(unsigned int) 0)
		address = frag_ptr->fr_address / OCTETS_PER_BYTE;

	      sprintf (data_buffer + data_buffer_size,
		       "%02X",
		       (frag_ptr->fr_literal[var_rep_idx]) & 0xff);
	      data_buffer_size += 2;

	      var_rep_idx++;
	      octet_in_frag++;

	      if ((offsetT) var_rep_idx >= frag_ptr->fr_fix + frag_ptr->fr_var)
		var_rep_idx = var_rep_max;
	    }
	}

      frag_ptr = frag_ptr->fr_next;
    }
  data_buffer[data_buffer_size] = '\0';
  return address;
}