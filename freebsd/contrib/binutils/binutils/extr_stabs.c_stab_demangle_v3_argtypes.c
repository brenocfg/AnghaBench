#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stab_handle {int dummy; } ;
struct TYPE_9__ {TYPE_3__* right; } ;
struct TYPE_10__ {TYPE_4__ s_binary; } ;
struct demangle_component {scalar_t__ type; TYPE_5__ u; } ;
typedef  int /*<<< orphan*/  debug_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_6__ {int /*<<< orphan*/  right; } ;
struct TYPE_7__ {TYPE_1__ s_binary; } ;
struct TYPE_8__ {scalar_t__ type; TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ DEMANGLE_COMPONENT_FUNCTION_TYPE ; 
 scalar_t__ DEMANGLE_COMPONENT_TYPED_NAME ; 
 int DMGL_ANSI ; 
 int DMGL_PARAMS ; 
 char* _ (char*) ; 
 struct demangle_component* cplus_demangle_v3_components (char const*,int,void**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  stab_bad_demangle (char const*) ; 
 int /*<<< orphan*/ * stab_demangle_v3_arglist (void*,struct stab_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static debug_type *
stab_demangle_v3_argtypes (void *dhandle, struct stab_handle *info,
			   const char *physname, bfd_boolean *pvarargs)
{
  struct demangle_component *dc;
  void *mem;
  debug_type *pargs;

  dc = cplus_demangle_v3_components (physname, DMGL_PARAMS | DMGL_ANSI, &mem);
  if (dc == NULL)
    {
      stab_bad_demangle (physname);
      return NULL;
    }

  /* We expect to see TYPED_NAME, and the right subtree describes the
     function type.  */
  if (dc->type != DEMANGLE_COMPONENT_TYPED_NAME
      || dc->u.s_binary.right->type != DEMANGLE_COMPONENT_FUNCTION_TYPE)
    {
      fprintf (stderr, _("Demangled name is not a function\n"));
      free (mem);
      return NULL;
    }

  pargs = stab_demangle_v3_arglist (dhandle, info,
				    dc->u.s_binary.right->u.s_binary.right,
				    pvarargs);

  free (mem);

  return pargs;
}