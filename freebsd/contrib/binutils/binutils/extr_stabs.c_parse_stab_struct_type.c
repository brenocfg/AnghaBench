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
typedef  int /*<<< orphan*/  debug_method ;
typedef  int /*<<< orphan*/  debug_field ;
typedef  int /*<<< orphan*/  debug_baseclass ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 scalar_t__ DEBUG_TYPE_NULL ; 
 scalar_t__ debug_make_object_type (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ debug_make_struct_type (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_number (char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_stab_baseclasses (void*,struct stab_handle*,char const**,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  parse_stab_members (void*,struct stab_handle*,char const*,char const**,int const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  parse_stab_struct_fields (void*,struct stab_handle*,char const**,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_stab_tilde_field (void*,struct stab_handle*,char const**,int const*,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static debug_type
parse_stab_struct_type (void *dhandle, struct stab_handle *info,
			const char *tagname, const char **pp,
			bfd_boolean structp, const int *typenums)
{
  const char *orig;
  bfd_vma size;
  debug_baseclass *baseclasses;
  debug_field *fields;
  bfd_boolean statics;
  debug_method *methods;
  debug_type vptrbase;
  bfd_boolean ownvptr;

  orig = *pp;

  /* Get the size.  */
  size = parse_number (pp, (bfd_boolean *) NULL);

  /* Get the other information.  */
  if (! parse_stab_baseclasses (dhandle, info, pp, &baseclasses)
      || ! parse_stab_struct_fields (dhandle, info, pp, &fields, &statics)
      || ! parse_stab_members (dhandle, info, tagname, pp, typenums, &methods)
      || ! parse_stab_tilde_field (dhandle, info, pp, typenums, &vptrbase,
				   &ownvptr))
    return DEBUG_TYPE_NULL;

  if (! statics
      && baseclasses == NULL
      && methods == NULL
      && vptrbase == DEBUG_TYPE_NULL
      && ! ownvptr)
    return debug_make_struct_type (dhandle, structp, size, fields);

  return debug_make_object_type (dhandle, structp, size, fields, baseclasses,
				 methods, vptrbase, ownvptr);
}