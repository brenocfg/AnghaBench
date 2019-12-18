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
struct ui_file {int dummy; } ;
struct type {int dummy; } ;
typedef  int LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  QUIT ; 
 int TYPE_FIELD_BITPOS (struct type*,unsigned int) ; 
 char* TYPE_FIELD_NAME (struct type*,unsigned int) ; 
 unsigned int TYPE_NFIELDS (struct type*) ; 
 unsigned int TYPE_N_BASECLASSES (struct type*) ; 
 int /*<<< orphan*/  builtin_type_int ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 int /*<<< orphan*/  pascal_type_print_base (struct type*,struct ui_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* type_name_no_tag (struct type*) ; 
 int unpack_long (int /*<<< orphan*/ ,char*) ; 

void
pascal_object_print_class_member (char *valaddr, struct type *domain,
				  struct ui_file *stream, char *prefix)
{

  /* VAL is a byte offset into the structure type DOMAIN.
     Find the name of the field for that offset and
     print it.  */
  int extra = 0;
  int bits = 0;
  unsigned int i;
  unsigned len = TYPE_NFIELDS (domain);
  /* @@ Make VAL into bit offset */
  LONGEST val = unpack_long (builtin_type_int, valaddr) << 3;
  for (i = TYPE_N_BASECLASSES (domain); i < len; i++)
    {
      int bitpos = TYPE_FIELD_BITPOS (domain, i);
      QUIT;
      if (val == bitpos)
	break;
      if (val < bitpos && i != 0)
	{
	  /* Somehow pointing into a field.  */
	  i -= 1;
	  extra = (val - TYPE_FIELD_BITPOS (domain, i));
	  if (extra & 0x7)
	    bits = 1;
	  else
	    extra >>= 3;
	  break;
	}
    }
  if (i < len)
    {
      char *name;
      fputs_filtered (prefix, stream);
      name = type_name_no_tag (domain);
      if (name)
	fputs_filtered (name, stream);
      else
	pascal_type_print_base (domain, stream, 0, 0);
      fprintf_filtered (stream, "::");
      fputs_filtered (TYPE_FIELD_NAME (domain, i), stream);
      if (extra)
	fprintf_filtered (stream, " + %d bytes", extra);
      if (bits)
	fprintf_filtered (stream, " (offset in bits)");
    }
  else
    fprintf_filtered (stream, "%ld", (long int) (val >> 3));
}