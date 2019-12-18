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
struct breakpoint {scalar_t__ type; char* triggered_dll_pathname; } ;
struct bpstats {struct bpstats* next; struct breakpoint* breakpoint_at; } ;
typedef  struct bpstats* bpstat ;

/* Variables and functions */
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 char* SOLIB_LOADED_LIBRARY_PATHNAME (int /*<<< orphan*/ ) ; 
 char* SOLIB_UNLOADED_LIBRARY_PATHNAME (int /*<<< orphan*/ ) ; 
 scalar_t__ bp_catch_catch ; 
 scalar_t__ bp_catch_load ; 
 scalar_t__ bp_catch_throw ; 
 scalar_t__ bp_catch_unload ; 
 struct bpstats* bpstat_alloc (struct breakpoint*,struct bpstats*) ; 
 int /*<<< orphan*/  bpstat_clear (struct bpstats**) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xmalloc (scalar_t__) ; 

void
bpstat_get_triggered_catchpoints (bpstat ep_list, bpstat *cp_list)
{
  struct bpstats root_bs[1];
  bpstat bs = root_bs;
  struct breakpoint *ep;
  char *dll_pathname;

  bpstat_clear (cp_list);
  root_bs->next = NULL;

  for (; ep_list != NULL; ep_list = ep_list->next)
    {
      /* Is this eventpoint a catchpoint?  If not, ignore it. */
      ep = ep_list->breakpoint_at;
      if (ep == NULL)
	break;
      if ((ep->type != bp_catch_load) &&
	  (ep->type != bp_catch_unload) &&
	  (ep->type != bp_catch_catch) &&
	  (ep->type != bp_catch_throw))		
	/* pai: (temp) ADD fork/vfork here!!  */
	continue;

      /* Yes; add it to the list. */
      bs = bpstat_alloc (ep, bs);
      *bs = *ep_list;
      bs->next = NULL;
      bs = root_bs->next;

#if defined(SOLIB_ADD)
      /* Also, for each triggered catchpoint, tag it with the name of
         the library that caused this trigger.  (We copy the name now,
         because it's only guaranteed to be available NOW, when the
         catchpoint triggers.  Clients who may wish to know the name
         later must get it from the catchpoint itself.) */
      if (ep->triggered_dll_pathname != NULL)
	xfree (ep->triggered_dll_pathname);
      if (ep->type == bp_catch_load)
	dll_pathname = SOLIB_LOADED_LIBRARY_PATHNAME (
	                 PIDGET (inferior_ptid));
      else
	dll_pathname = SOLIB_UNLOADED_LIBRARY_PATHNAME (
	                 PIDGET (inferior_ptid));
#else
      dll_pathname = NULL;
#endif
      if (dll_pathname)
	{
	  ep->triggered_dll_pathname = (char *) 
	    xmalloc (strlen (dll_pathname) + 1);
	  strcpy (ep->triggered_dll_pathname, dll_pathname);
	}
      else
	ep->triggered_dll_pathname = NULL;
    }

  *cp_list = bs;
}