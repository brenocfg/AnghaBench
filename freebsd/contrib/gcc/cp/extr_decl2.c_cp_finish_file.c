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
typedef  int /*<<< orphan*/  location_t ;

/* Variables and functions */
 int /*<<< orphan*/  TV_VARCONST ; 
 int at_eof ; 
 scalar_t__ current_class_type ; 
 scalar_t__ decl_namespace_list ; 
 int /*<<< orphan*/  emit_deferred (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_instantiate_pending_templates (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_support_tinfos () ; 
 int /*<<< orphan*/  global_bindings_p () ; 
 int input_line ; 
 int /*<<< orphan*/  input_location ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

void
cp_finish_file (void)
{
  /* APPLE LOCAL begin radar 4721858 */
  location_t locus;
  /* APPLE LOCAL end radar 4721858 */
  
  locus = input_location;
  at_eof = 1;

  /* Bad parse errors.  Just forget about it.  */
  if (! global_bindings_p () || current_class_type || decl_namespace_list)
    return;

  /* APPLE LOCAL radar 4874613 */
  /* dump of pch file moved to c_parse_file (). */

#ifdef USE_MAPPED_LOCATION
  /* FIXME - huh? */
#else
  /* Otherwise, GDB can get confused, because in only knows
     about source for LINENO-1 lines.  */
  input_line -= 1;
#endif

  /* We now have to write out all the stuff we put off writing out.
     These include:

       o Template specializations that we have not yet instantiated,
	 but which are needed.
       o Initialization and destruction for non-local objects with
	 static storage duration.  (Local objects with static storage
	 duration are initialized when their scope is first entered,
	 and are cleaned up via atexit.)
       o Virtual function tables.

     All of these may cause others to be needed.  For example,
     instantiating one function may cause another to be needed, and
     generating the initializer for an object may cause templates to be
     instantiated, etc., etc.  */

  timevar_push (TV_VARCONST);

  emit_support_tinfos ();

  /* APPLE LOCAL begin radar 4721858 */
  emit_instantiate_pending_templates (&locus);

  emit_deferred (&locus);
}