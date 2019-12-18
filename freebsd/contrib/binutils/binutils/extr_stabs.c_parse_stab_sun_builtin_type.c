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
typedef  int /*<<< orphan*/  debug_type ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TYPE_NULL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bad_stab (char const*) ; 
 int /*<<< orphan*/  debug_make_int_type (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_make_void_type (void*) ; 
 int parse_number (char const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static debug_type
parse_stab_sun_builtin_type (void *dhandle, const char **pp)
{
  const char *orig;
  bfd_boolean unsignedp;
  bfd_vma bits;

  orig = *pp;

  switch (**pp)
    {
    case 's':
      unsignedp = FALSE;
      break;
    case 'u':
      unsignedp = TRUE;
      break;
    default:
      bad_stab (orig);
      return DEBUG_TYPE_NULL;
    }
  ++*pp;

  /* For some odd reason, all forms of char put a c here.  This is strange
     because no other type has this honor.  We can safely ignore this because
     we actually determine 'char'acterness by the number of bits specified in
     the descriptor.  */
  if (**pp == 'c')
    ++*pp;

  /* The first number appears to be the number of bytes occupied
     by this type, except that unsigned short is 4 instead of 2.
     Since this information is redundant with the third number,
     we will ignore it.  */
  (void) parse_number (pp, (bfd_boolean *) NULL);
  if (**pp != ';')
    {
      bad_stab (orig);
      return DEBUG_TYPE_NULL;
    }
  ++*pp;

  /* The second number is always 0, so ignore it too.  */
  (void) parse_number (pp, (bfd_boolean *) NULL);
  if (**pp != ';')
    {
      bad_stab (orig);
      return DEBUG_TYPE_NULL;
    }
  ++*pp;

  /* The third number is the number of bits for this type.  */
  bits = parse_number (pp, (bfd_boolean *) NULL);

  /* The type *should* end with a semicolon.  If it are embedded
     in a larger type the semicolon may be the only way to know where
     the type ends.  If this type is at the end of the stabstring we
     can deal with the omitted semicolon (but we don't have to like
     it).  Don't bother to complain(), Sun's compiler omits the semicolon
     for "void".  */
  if (**pp == ';')
    ++*pp;

  if (bits == 0)
    return debug_make_void_type (dhandle);

  return debug_make_int_type (dhandle, bits / 8, unsignedp);
}