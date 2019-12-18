#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  windres_bfd ;
typedef  int rc_uint_type ;
struct TYPE_11__ {unsigned long id; } ;
struct TYPE_13__ {TYPE_1__ u; int /*<<< orphan*/  named; } ;
typedef  TYPE_3__ const rc_res_id ;
struct TYPE_12__ {int /*<<< orphan*/  res; TYPE_5__* dir; } ;
struct TYPE_14__ {TYPE_2__ u; scalar_t__ subdir; TYPE_3__ const id; struct TYPE_14__* next; } ;
typedef  TYPE_4__ rc_res_entry ;
struct TYPE_15__ {TYPE_4__* entries; } ;
typedef  TYPE_5__ rc_res_directory ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int write_res_resource (int /*<<< orphan*/ *,int,TYPE_3__ const*,TYPE_3__ const*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static rc_uint_type
write_res_directory (windres_bfd *wrbfd, rc_uint_type off, const rc_res_directory *rd,
		     const rc_res_id *type, const rc_res_id *name, rc_uint_type *language,
		     int level)
{
  const rc_res_entry *re;

  for (re = rd->entries; re != NULL; re = re->next)
    {
      switch (level)
	{
	case 1:
	  /* If we're at level 1, the key of this resource is the
	     type.  This normally duplicates the information we have
	     stored with the resource itself, but we need to remember
	     the type if this is a user define resource type.  */
	  type = &re->id;
	  break;

	case 2:
	  /* If we're at level 2, the key of this resource is the name
	     we are going to use in the rc printout.  */
	  name = &re->id;
	  break;

	case 3:
	  /* If we're at level 3, then this key represents a language.
	     Use it to update the current language.  */
	  if (! re->id.named
	      && re->id.u.id != (unsigned long) *language
	      && (re->id.u.id & 0xffff) == re->id.u.id)
	    {
	      *language = re->id.u.id;
	    }
	  break;

	default:
	  break;
	}

      if (re->subdir)
	off = write_res_directory (wrbfd, off, re->u.dir, type, name, language,
				   level + 1);
      else
	{
	  if (level == 3)
	    {
	      /* This is the normal case: the three levels are
	         TYPE/NAME/LANGUAGE.  NAME will have been set at level
	         2, and represents the name to use.  We probably just
	         set LANGUAGE, and it will probably match what the
	         resource itself records if anything.  */
	      off = write_res_resource (wrbfd, off, type, name, re->u.res,
	      				language);
	    }
	  else
	    {
	      fprintf (stderr, "// Resource at unexpected level %d\n", level);
	      off = write_res_resource (wrbfd, off, type, (rc_res_id *) NULL,
	      				re->u.res, language);
	    }
	}
    }

  return off;
}