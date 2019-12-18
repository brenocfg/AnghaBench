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
struct stab_handle {int dummy; } ;
typedef  scalar_t__ debug_type ;
typedef  int bfd_vma ;
typedef  int bfd_signed_vma ;
typedef  int bfd_boolean ;

/* Variables and functions */
 scalar_t__ CONST_STRNEQ (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ DEBUG_TYPE_NULL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LLHIGH ; 
 int /*<<< orphan*/  LLLOW ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ULLHIGH ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bad_stab (char const*) ; 
 scalar_t__ debug_make_complex_type (void*,int) ; 
 scalar_t__ debug_make_float_type (void*,int) ; 
 scalar_t__ debug_make_int_type (void*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ debug_make_range_type (void*,scalar_t__,int,int) ; 
 scalar_t__ debug_make_void_type (void*) ; 
 int parse_number (char const**,int*) ; 
 scalar_t__ parse_stab_type (void*,struct stab_handle*,char const*,char const**,scalar_t__**) ; 
 int /*<<< orphan*/  parse_stab_type_number (char const**,int*) ; 
 scalar_t__ stab_find_type (void*,struct stab_handle*,int*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  warn_stab (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static debug_type
parse_stab_range_type (void *dhandle, struct stab_handle *info, const char *typename, const char **pp, const int *typenums)
{
  const char *orig;
  int rangenums[2];
  bfd_boolean self_subrange;
  debug_type index_type;
  const char *s2, *s3;
  bfd_signed_vma n2, n3;
  bfd_boolean ov2, ov3;

  orig = *pp;

  index_type = DEBUG_TYPE_NULL;

  /* First comes a type we are a subrange of.
     In C it is usually 0, 1 or the type being defined.  */
  if (! parse_stab_type_number (pp, rangenums))
    return DEBUG_TYPE_NULL;

  self_subrange = (rangenums[0] == typenums[0]
		   && rangenums[1] == typenums[1]);

  if (**pp == '=')
    {
      *pp = orig;
      index_type = parse_stab_type (dhandle, info, (const char *) NULL,
				    pp, (debug_type **) NULL);
      if (index_type == DEBUG_TYPE_NULL)
	return DEBUG_TYPE_NULL;
    }

  if (**pp == ';')
    ++*pp;

  /* The remaining two operands are usually lower and upper bounds of
     the range.  But in some special cases they mean something else.  */
  s2 = *pp;
  n2 = parse_number (pp, &ov2);
  if (**pp != ';')
    {
      bad_stab (orig);
      return DEBUG_TYPE_NULL;
    }
  ++*pp;

  s3 = *pp;
  n3 = parse_number (pp, &ov3);
  if (**pp != ';')
    {
      bad_stab (orig);
      return DEBUG_TYPE_NULL;
    }
  ++*pp;

  if (ov2 || ov3)
    {
      /* gcc will emit range stabs for long long types.  Handle this
         as a special case.  FIXME: This needs to be more general.  */
#define LLLOW   "01000000000000000000000;"
#define LLHIGH   "0777777777777777777777;"
#define ULLHIGH "01777777777777777777777;"
      if (index_type == DEBUG_TYPE_NULL)
	{
	  if (CONST_STRNEQ (s2, LLLOW)
	      && CONST_STRNEQ (s3, LLHIGH))
	    return debug_make_int_type (dhandle, 8, FALSE);
	  if (! ov2
	      && n2 == 0
	      && CONST_STRNEQ (s3, ULLHIGH))
	    return debug_make_int_type (dhandle, 8, TRUE);
	}

      warn_stab (orig, _("numeric overflow"));
    }

  if (index_type == DEBUG_TYPE_NULL)
    {
      /* A type defined as a subrange of itself, with both bounds 0,
         is void.  */
      if (self_subrange && n2 == 0 && n3 == 0)
	return debug_make_void_type (dhandle);

      /* A type defined as a subrange of itself, with n2 positive and
	 n3 zero, is a complex type, and n2 is the number of bytes.  */
      if (self_subrange && n3 == 0 && n2 > 0)
	return debug_make_complex_type (dhandle, n2);

      /* If n3 is zero and n2 is positive, this is a floating point
         type, and n2 is the number of bytes.  */
      if (n3 == 0 && n2 > 0)
	return debug_make_float_type (dhandle, n2);

      /* If the upper bound is -1, this is an unsigned int.  */
      if (n2 == 0 && n3 == -1)
	{
	  /* When gcc is used with -gstabs, but not -gstabs+, it will emit
	         long long int:t6=r1;0;-1;
		 long long unsigned int:t7=r1;0;-1;
	     We hack here to handle this reasonably.  */
	  if (typename != NULL)
	    {
	      if (strcmp (typename, "long long int") == 0)
		return debug_make_int_type (dhandle, 8, FALSE);
	      else if (strcmp (typename, "long long unsigned int") == 0)
		return debug_make_int_type (dhandle, 8, TRUE);
	    }
	  /* FIXME: The size here really depends upon the target.  */
	  return debug_make_int_type (dhandle, 4, TRUE);
	}

      /* A range of 0 to 127 is char.  */
      if (self_subrange && n2 == 0 && n3 == 127)
	return debug_make_int_type (dhandle, 1, FALSE);

      /* FIXME: gdb checks for the language CHILL here.  */

      if (n2 == 0)
	{
	  if (n3 < 0)
	    return debug_make_int_type (dhandle, - n3, TRUE);
	  else if (n3 == 0xff)
	    return debug_make_int_type (dhandle, 1, TRUE);
	  else if (n3 == 0xffff)
	    return debug_make_int_type (dhandle, 2, TRUE);
	  else if (n3 == (bfd_signed_vma) 0xffffffff)
	    return debug_make_int_type (dhandle, 4, TRUE);
#ifdef BFD64
	  else if (n3 == ((((bfd_signed_vma) 0xffffffff) << 32) | 0xffffffff))
	    return debug_make_int_type (dhandle, 8, TRUE);
#endif
	}
      else if (n3 == 0
	       && n2 < 0
	       && (self_subrange || n2 == -8))
	return debug_make_int_type (dhandle, - n2, TRUE);
      else if (n2 == - n3 - 1 || n2 == n3 + 1)
	{
	  if (n3 == 0x7f)
	    return debug_make_int_type (dhandle, 1, FALSE);
	  else if (n3 == 0x7fff)
	    return debug_make_int_type (dhandle, 2, FALSE);
	  else if (n3 == 0x7fffffff)
	    return debug_make_int_type (dhandle, 4, FALSE);
#ifdef BFD64
	  else if (n3 == ((((bfd_vma) 0x7fffffff) << 32) | 0xffffffff))
	    return debug_make_int_type (dhandle, 8, FALSE);
#endif
	}
    }

  /* At this point I don't have the faintest idea how to deal with a
     self_subrange type; I'm going to assume that this is used as an
     idiom, and that all of them are special cases.  So . . .  */
  if (self_subrange)
    {
      bad_stab (orig);
      return DEBUG_TYPE_NULL;
    }

  index_type = stab_find_type (dhandle, info, rangenums);
  if (index_type == DEBUG_TYPE_NULL)
    {
      /* Does this actually ever happen?  Is that why we are worrying
         about dealing with it rather than just calling error_type?  */
      warn_stab (orig, _("missing index type"));
      index_type = debug_make_int_type (dhandle, 4, FALSE);
    }

  return debug_make_range_type (dhandle, index_type, n2, n3);
}