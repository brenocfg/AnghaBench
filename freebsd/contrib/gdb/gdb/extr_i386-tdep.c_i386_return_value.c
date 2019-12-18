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
struct regcache {int dummy; } ;
struct gdbarch {int dummy; } ;
typedef  enum type_code { ____Placeholder_type_code } type_code ;
typedef  enum return_value_convention { ____Placeholder_return_value_convention } return_value_convention ;

/* Variables and functions */
 int RETURN_VALUE_REGISTER_CONVENTION ; 
 int RETURN_VALUE_STRUCT_CONVENTION ; 
 int TYPE_CODE (struct type*) ; 
 int TYPE_CODE_STRUCT ; 
 int TYPE_CODE_UNION ; 
 int /*<<< orphan*/  TYPE_FIELD_TYPE (struct type*,int /*<<< orphan*/ ) ; 
 int TYPE_NFIELDS (struct type*) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i386_extract_return_value (struct gdbarch*,struct type*,struct regcache*,void*) ; 
 int /*<<< orphan*/  i386_reg_struct_return_p (struct gdbarch*,struct type*) ; 
 int /*<<< orphan*/  i386_store_return_value (struct gdbarch*,struct type*,struct regcache*,void const*) ; 

__attribute__((used)) static enum return_value_convention
i386_return_value (struct gdbarch *gdbarch, struct type *type,
		   struct regcache *regcache, void *readbuf,
		   const void *writebuf)
{
  enum type_code code = TYPE_CODE (type);

  if ((code == TYPE_CODE_STRUCT || code == TYPE_CODE_UNION)
      && !i386_reg_struct_return_p (gdbarch, type))
    return RETURN_VALUE_STRUCT_CONVENTION;

  /* This special case is for structures consisting of a single
     `float' or `double' member.  These structures are returned in
     %st(0).  For these structures, we call ourselves recursively,
     changing TYPE into the type of the first member of the structure.
     Since that should work for all structures that have only one
     member, we don't bother to check the member's type here.  */
  if (code == TYPE_CODE_STRUCT && TYPE_NFIELDS (type) == 1)
    {
      type = check_typedef (TYPE_FIELD_TYPE (type, 0));
      return i386_return_value (gdbarch, type, regcache, readbuf, writebuf);
    }

  if (readbuf)
    i386_extract_return_value (gdbarch, type, regcache, readbuf);
  if (writebuf)
    i386_store_return_value (gdbarch, type, regcache, writebuf);

  return RETURN_VALUE_REGISTER_CONVENTION;
}