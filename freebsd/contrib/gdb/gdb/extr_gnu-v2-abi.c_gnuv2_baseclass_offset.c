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
struct type {int dummy; } ;
typedef  int LONGEST ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 scalar_t__ BASETYPE_VIA_VIRTUAL (struct type*,int) ; 
 struct type* TYPE_BASECLASS (struct type*,int) ; 
 int TYPE_BASECLASS_BITPOS (struct type*,int) ; 
 int TYPE_FIELD_BITPOS (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_FIELD_TYPE (struct type*,int) ; 
 int TYPE_NFIELDS (struct type*) ; 
 int TYPE_N_BASECLASSES (struct type*) ; 
 int baseclass_offset (struct type*,int,char*,int) ; 
 int unpack_pointer (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ vb_match (struct type*,int,struct type*) ; 

int
gnuv2_baseclass_offset (struct type *type, int index, char *valaddr,
		  CORE_ADDR address)
{
  struct type *basetype = TYPE_BASECLASS (type, index);

  if (BASETYPE_VIA_VIRTUAL (type, index))
    {
      /* Must hunt for the pointer to this virtual baseclass.  */
      int i, len = TYPE_NFIELDS (type);
      int n_baseclasses = TYPE_N_BASECLASSES (type);

      /* First look for the virtual baseclass pointer
         in the fields.  */
      for (i = n_baseclasses; i < len; i++)
	{
	  if (vb_match (type, i, basetype))
	    {
	      CORE_ADDR addr
	      = unpack_pointer (TYPE_FIELD_TYPE (type, i),
				valaddr + (TYPE_FIELD_BITPOS (type, i) / 8));

	      return addr - (LONGEST) address;
	    }
	}
      /* Not in the fields, so try looking through the baseclasses.  */
      for (i = index + 1; i < n_baseclasses; i++)
	{
	  int boffset =
	  baseclass_offset (type, i, valaddr, address);
	  if (boffset)
	    return boffset;
	}
      /* Not found.  */
      return -1;
    }

  /* Baseclass is easily computed.  */
  return TYPE_BASECLASS_BITPOS (type, index) / 8;
}