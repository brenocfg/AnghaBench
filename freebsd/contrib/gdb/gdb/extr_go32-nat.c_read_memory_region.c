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

/* Variables and functions */
 int __dpmi_allocate_ldt_descriptors (int) ; 
 int /*<<< orphan*/  __dpmi_free_ldt_descriptor (int) ; 
 int __dpmi_get_descriptor_access_rights (int) ; 
 size_t __dpmi_get_segment_limit (int) ; 
 int __dpmi_set_descriptor_access_rights (int,int) ; 
 int __dpmi_set_segment_base_address (int,unsigned long) ; 
 int __dpmi_set_segment_limit (int,size_t) ; 
 int _dos_ds ; 
 int /*<<< orphan*/  _my_ds () ; 
 int /*<<< orphan*/  dosmemget (unsigned long,size_t,void*) ; 
 int /*<<< orphan*/  movedata (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,size_t) ; 

__attribute__((used)) static int
read_memory_region (unsigned long addr, void *dest, size_t len)
{
  unsigned long dos_ds_limit = __dpmi_get_segment_limit (_dos_ds);
  int retval = 1;

  /* For the low memory, we can simply use _dos_ds.  */
  if (addr <= dos_ds_limit - len)
    dosmemget (addr, len, dest);
  else
    {
      /* For memory above 1MB we need to set up a special segment to
	 be able to access that memory.  */
      int sel = __dpmi_allocate_ldt_descriptors (1);

      if (sel <= 0)
	retval = 0;
      else
	{
	  int access_rights = __dpmi_get_descriptor_access_rights (sel);
	  size_t segment_limit = len - 1;

	  /* Make sure the crucial bits in the descriptor access
	     rights are set correctly.  Some DPMI providers might barf
	     if we set the segment limit to something that is not an
	     integral multiple of 4KB pages if the granularity bit is
	     not set to byte-granular, even though the DPMI spec says
	     it's the host's responsibility to set that bit correctly.  */
	  if (len > 1024 * 1024)
	    {
	      access_rights |= 0x8000;
	      /* Page-granular segments should have the low 12 bits of
		 the limit set.  */
	      segment_limit |= 0xfff;
	    }
	  else
	    access_rights &= ~0x8000;

	  if (__dpmi_set_segment_base_address (sel, addr) != -1
	      && __dpmi_set_descriptor_access_rights (sel, access_rights) != -1
	      && __dpmi_set_segment_limit (sel, segment_limit) != -1
	      /* W2K silently fails to set the segment limit, leaving
		 it at zero; this test avoids the resulting crash.  */
	      && __dpmi_get_segment_limit (sel) >= segment_limit)
	    movedata (sel, 0, _my_ds (), (unsigned)dest, len);
	  else
	    retval = 0;

	  __dpmi_free_ldt_descriptor (sel);
	}
    }
  return retval;
}