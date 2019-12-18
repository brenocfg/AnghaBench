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
typedef  int /*<<< orphan*/ * tree ;
struct reachable_info {int /*<<< orphan*/  saw_any_handlers; int /*<<< orphan*/ * types_allowed; int /*<<< orphan*/ * types_caught; } ;
struct TYPE_8__ {int /*<<< orphan*/ * type_list; } ;
struct TYPE_7__ {int /*<<< orphan*/ * type_list; struct eh_region* next_catch; } ;
struct TYPE_6__ {struct eh_region* catch; } ;
struct TYPE_9__ {TYPE_3__ allowed; TYPE_2__ catch; TYPE_1__ try; } ;
struct eh_region {int type; TYPE_4__ u; } ;
typedef  enum reachable_code { ____Placeholder_reachable_code } reachable_code ;
struct TYPE_10__ {int /*<<< orphan*/  after_inlining; } ;

/* Variables and functions */
#define  ERT_ALLOWED_EXCEPTIONS 134 
#define  ERT_CATCH 133 
#define  ERT_CLEANUP 132 
#define  ERT_MUST_NOT_THROW 131 
#define  ERT_THROW 130 
#define  ERT_TRY 129 
#define  ERT_UNKNOWN 128 
 int /*<<< orphan*/ * NULL_TREE ; 
 int RNL_BLOCKED ; 
 int RNL_CAUGHT ; 
 int RNL_MAYBE_CAUGHT ; 
 int RNL_NOT_CAUGHT ; 
 int /*<<< orphan*/ * TREE_CHAIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_VALUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_reachable_handler (struct reachable_info*,struct eh_region*,struct eh_region*) ; 
 TYPE_5__* cfun ; 
 int /*<<< orphan*/  check_handled (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  lang_eh_type_covers (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* tree_cons (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum reachable_code
reachable_next_level (struct eh_region *region, tree type_thrown,
		      struct reachable_info *info)
{
  switch (region->type)
    {
    case ERT_CLEANUP:
      /* Before landing-pad generation, we model control flow
	 directly to the individual handlers.  In this way we can
	 see that catch handler types may shadow one another.  */
      add_reachable_handler (info, region, region);
      return RNL_MAYBE_CAUGHT;

    case ERT_TRY:
      {
	struct eh_region *c;
	enum reachable_code ret = RNL_NOT_CAUGHT;

	for (c = region->u.try.catch; c ; c = c->u.catch.next_catch)
	  {
	    /* A catch-all handler ends the search.  */
	    if (c->u.catch.type_list == NULL)
	      {
		add_reachable_handler (info, region, c);
		return RNL_CAUGHT;
	      }

	    if (type_thrown)
	      {
		/* If we have at least one type match, end the search.  */
		tree tp_node = c->u.catch.type_list;

		for (; tp_node; tp_node = TREE_CHAIN (tp_node))
		  {
		    tree type = TREE_VALUE (tp_node);

		    if (type == type_thrown
			|| (lang_eh_type_covers
			    && (*lang_eh_type_covers) (type, type_thrown)))
		      {
			add_reachable_handler (info, region, c);
			return RNL_CAUGHT;
		      }
		  }

		/* If we have definitive information of a match failure,
		   the catch won't trigger.  */
		if (lang_eh_type_covers)
		  return RNL_NOT_CAUGHT;
	      }

	    /* At this point, we either don't know what type is thrown or
	       don't have front-end assistance to help deciding if it is
	       covered by one of the types in the list for this region.

	       We'd then like to add this region to the list of reachable
	       handlers since it is indeed potentially reachable based on the
	       information we have.

	       Actually, this handler is for sure not reachable if all the
	       types it matches have already been caught. That is, it is only
	       potentially reachable if at least one of the types it catches
	       has not been previously caught.  */

	    if (! info)
	      ret = RNL_MAYBE_CAUGHT;
	    else
	      {
		tree tp_node = c->u.catch.type_list;
		bool maybe_reachable = false;

		/* Compute the potential reachability of this handler and
		   update the list of types caught at the same time.  */
		for (; tp_node; tp_node = TREE_CHAIN (tp_node))
		  {
		    tree type = TREE_VALUE (tp_node);

		    if (! check_handled (info->types_caught, type))
		      {
			info->types_caught
			  = tree_cons (NULL, type, info->types_caught);

			maybe_reachable = true;
		      }
		  }

		if (maybe_reachable)
		  {
		    add_reachable_handler (info, region, c);

		    /* ??? If the catch type is a base class of every allowed
		       type, then we know we can stop the search.  */
		    ret = RNL_MAYBE_CAUGHT;
		  }
	      }
	  }

	return ret;
      }

    case ERT_ALLOWED_EXCEPTIONS:
      /* An empty list of types definitely ends the search.  */
      if (region->u.allowed.type_list == NULL_TREE)
	{
	  add_reachable_handler (info, region, region);
	  return RNL_CAUGHT;
	}

      /* Collect a list of lists of allowed types for use in detecting
	 when a catch may be transformed into a catch-all.  */
      if (info)
	info->types_allowed = tree_cons (NULL_TREE,
					 region->u.allowed.type_list,
					 info->types_allowed);

      /* If we have definitive information about the type hierarchy,
	 then we can tell if the thrown type will pass through the
	 filter.  */
      if (type_thrown && lang_eh_type_covers)
	{
	  if (check_handled (region->u.allowed.type_list, type_thrown))
	    return RNL_NOT_CAUGHT;
	  else
	    {
	      add_reachable_handler (info, region, region);
	      return RNL_CAUGHT;
	    }
	}

      add_reachable_handler (info, region, region);
      return RNL_MAYBE_CAUGHT;

    case ERT_CATCH:
      /* Catch regions are handled by their controlling try region.  */
      return RNL_NOT_CAUGHT;

    case ERT_MUST_NOT_THROW:
      /* Here we end our search, since no exceptions may propagate.
	 If we've touched down at some landing pad previous, then the
	 explicit function call we generated may be used.  Otherwise
	 the call is made by the runtime.

         Before inlining, do not perform this optimization.  We may
	 inline a subroutine that contains handlers, and that will
	 change the value of saw_any_handlers.  */

      if ((info && info->saw_any_handlers) || !cfun->after_inlining)
	{
	  add_reachable_handler (info, region, region);
	  return RNL_CAUGHT;
	}
      else
	return RNL_BLOCKED;

    case ERT_THROW:
    case ERT_UNKNOWN:
      /* Shouldn't see these here.  */
      gcc_unreachable ();
      break;
    default:
      gcc_unreachable ();
    }
}