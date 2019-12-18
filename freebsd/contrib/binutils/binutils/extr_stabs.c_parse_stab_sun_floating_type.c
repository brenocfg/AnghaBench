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
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TYPE_NULL ; 
 scalar_t__ NF_COMPLEX ; 
 scalar_t__ NF_COMPLEX16 ; 
 scalar_t__ NF_COMPLEX32 ; 
 int /*<<< orphan*/  bad_stab (char const*) ; 
 int /*<<< orphan*/  debug_make_complex_type (void*,scalar_t__) ; 
 int /*<<< orphan*/  debug_make_float_type (void*,scalar_t__) ; 
 scalar_t__ parse_number (char const**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static debug_type
parse_stab_sun_floating_type (void *dhandle, const char **pp)
{
  const char *orig;
  bfd_vma details;
  bfd_vma bytes;

  orig = *pp;

  /* The first number has more details about the type, for example
     FN_COMPLEX.  */
  details = parse_number (pp, (bfd_boolean *) NULL);
  if (**pp != ';')
    {
      bad_stab (orig);
      return DEBUG_TYPE_NULL;
    }

  /* The second number is the number of bytes occupied by this type */
  bytes = parse_number (pp, (bfd_boolean *) NULL);
  if (**pp != ';')
    {
      bad_stab (orig);
      return DEBUG_TYPE_NULL;
    }

  if (details == NF_COMPLEX
      || details == NF_COMPLEX16
      || details == NF_COMPLEX32)
    return debug_make_complex_type (dhandle, bytes);

  return debug_make_float_type (dhandle, bytes);
}