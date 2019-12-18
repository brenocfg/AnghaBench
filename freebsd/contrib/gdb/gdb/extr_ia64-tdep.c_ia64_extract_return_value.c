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
typedef  int /*<<< orphan*/  ULONGEST ;

/* Variables and functions */
 int IA64_FR8_REGNUM ; 
 int IA64_GR8_REGNUM ; 
 int MAX_REGISTER_SIZE ; 
 int TYPE_LENGTH (struct type*) ; 
 int /*<<< orphan*/  builtin_type_ia64_ext ; 
 int /*<<< orphan*/  convert_typed_floating (char*,int /*<<< orphan*/ ,char*,struct type*) ; 
 struct type* ia64_register_type (int /*<<< orphan*/ *,int) ; 
 struct type* is_float_or_hfa_type (struct type*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  regcache_cooked_read (struct regcache*,int,char*) ; 
 int /*<<< orphan*/  regcache_cooked_read_unsigned (struct regcache*,int,int /*<<< orphan*/ *) ; 

void
ia64_extract_return_value (struct type *type, struct regcache *regcache, void *valbuf)
{
  struct type *float_elt_type;

  float_elt_type = is_float_or_hfa_type (type);
  if (float_elt_type != NULL)
    {
      char from[MAX_REGISTER_SIZE];
      int offset = 0;
      int regnum = IA64_FR8_REGNUM;
      int n = TYPE_LENGTH (type) / TYPE_LENGTH (float_elt_type);

      while (n-- > 0)
	{
	  regcache_cooked_read (regcache, regnum, from);
	  convert_typed_floating (from, builtin_type_ia64_ext,
				  (char *)valbuf + offset, float_elt_type);	  
	  offset += TYPE_LENGTH (float_elt_type);
	  regnum++;
	}
    }
  else
    {
      ULONGEST val;
      int offset = 0;
      int regnum = IA64_GR8_REGNUM;
      int reglen = TYPE_LENGTH (ia64_register_type (NULL, IA64_GR8_REGNUM));
      int n = TYPE_LENGTH (type) / reglen;
      int m = TYPE_LENGTH (type) % reglen;

      while (n-- > 0)
	{
	  ULONGEST val;
	  regcache_cooked_read_unsigned (regcache, regnum, &val);
	  memcpy ((char *)valbuf + offset, &val, reglen);
	  offset += reglen;
	  regnum++;
	}

      if (m)
	{
          regcache_cooked_read_unsigned (regcache, regnum, &val);
	  memcpy ((char *)valbuf + offset, &val, m);
	}
    }
}