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
struct TYPE_2__ {int text_base; int text_size; } ;
struct so_list {char* name; struct so_list* next; TYPE_1__ pa64_solib_desc; } ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 struct so_list* so_list_head ; 

char *
pa64_solib_address (CORE_ADDR addr)
{
  struct so_list *so = so_list_head;

  while (so)
    {
      /* Is this address within this shlib's text range?  If so,
	 return the shlib's name.  */
      if (addr >= so->pa64_solib_desc.text_base
	  && addr < (so->pa64_solib_desc.text_base
		     | so->pa64_solib_desc.text_size))
	return so->name;

      /* Nope, keep looking... */
      so = so->next;
    }

  /* No, we couldn't prove that the address is within a shlib. */
  return NULL;
}