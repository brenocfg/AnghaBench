#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ieee_handle {TYPE_3__* type_stack; } ;
typedef  enum debug_visibility { ____Placeholder_debug_visibility } debug_visibility ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_5__ {TYPE_1__* classdef; } ;
struct TYPE_6__ {TYPE_2__ type; } ;
struct TYPE_4__ {unsigned int indx; int pmisccount; int /*<<< orphan*/  pmiscbuf; } ;

/* Variables and functions */
 unsigned int CXXFLAGS_STATIC ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ieee_change_buffer (struct ieee_handle*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee_pop_unused_type (struct ieee_handle*) ; 
 unsigned int ieee_vis_to_flags (int) ; 
 int /*<<< orphan*/  ieee_write_asn (struct ieee_handle*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ieee_write_atn65 (struct ieee_handle*,unsigned int,char const*) ; 

__attribute__((used)) static bfd_boolean
ieee_class_static_member (void *p, const char *name, const char *physname,
			  enum debug_visibility visibility)
{
  struct ieee_handle *info = (struct ieee_handle *) p;
  unsigned int flags;
  unsigned int nindx;

  /* We don't care about the type.  Hopefully there will be a call to
     ieee_variable declaring the physical name and the type, since
     that is where an IEEE consumer must get the type.  */
  ieee_pop_unused_type (info);

  assert (info->type_stack != NULL
	  && info->type_stack->type.classdef != NULL);

  flags = ieee_vis_to_flags (visibility);
  flags |= CXXFLAGS_STATIC;

  nindx = info->type_stack->type.classdef->indx;

  if (! ieee_change_buffer (info, &info->type_stack->type.classdef->pmiscbuf)
      || ! ieee_write_asn (info, nindx, 'd')
      || ! ieee_write_asn (info, nindx, flags)
      || ! ieee_write_atn65 (info, nindx, name)
      || ! ieee_write_atn65 (info, nindx, physname))
    return FALSE;
  info->type_stack->type.classdef->pmisccount += 4;

  return TRUE;
}