#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int rc_uint_type ;
struct TYPE_14__ {unsigned long id; } ;
struct TYPE_16__ {TYPE_1__ u; int /*<<< orphan*/  named; } ;
typedef  TYPE_3__ const rc_res_id ;
struct TYPE_15__ {int /*<<< orphan*/  res; } ;
struct TYPE_17__ {TYPE_2__ u; scalar_t__ subdir; TYPE_3__ const id; struct TYPE_17__* next; } ;
typedef  TYPE_4__ rc_res_entry ;
struct TYPE_18__ {scalar_t__ time; scalar_t__ characteristics; scalar_t__ major; scalar_t__ minor; TYPE_4__* entries; } ;
typedef  TYPE_5__ rc_res_directory ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int SUBLANG_SHIFT ; 
 int /*<<< orphan*/  wr_print (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  wr_print_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr_printcomment (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  write_rc_resource (int /*<<< orphan*/ *,TYPE_3__ const*,TYPE_3__ const*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  write_rc_subdir (int /*<<< orphan*/ *,TYPE_4__ const*,TYPE_3__ const*,TYPE_3__ const*,int*,int) ; 

__attribute__((used)) static void
write_rc_directory (FILE *e, const rc_res_directory *rd,
		    const rc_res_id *type, const rc_res_id *name,
		    rc_uint_type *language, int level)
{
  const rc_res_entry *re;

  /* Print out some COFF information that rc files can't represent.  */
  if (rd->time != 0 || rd->characteristics != 0 || rd->major != 0 || rd->minor != 0)
    {
      wr_printcomment (e, "COFF information not part of RC");
  if (rd->time != 0)
	wr_printcomment (e, "Time stamp: %u", rd->time);
  if (rd->characteristics != 0)
	wr_printcomment (e, "Characteristics: %u", rd->characteristics);
  if (rd->major != 0 || rd->minor != 0)
	wr_printcomment (e, "Version major:%d minor:%d", rd->major, rd->minor);
    }

  for (re = rd->entries;  re != NULL; re = re->next)
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
	      && re->id.u.id != (unsigned long) (unsigned int) *language
	      && (re->id.u.id & 0xffff) == re->id.u.id)
	    {
	      wr_print (e, "LANGUAGE %u, %u\n",
		       re->id.u.id & ((1 << SUBLANG_SHIFT) - 1),
		       (re->id.u.id >> SUBLANG_SHIFT) & 0xff);
	      *language = re->id.u.id;
	    }
	  break;

	default:
	  break;
	}

      if (re->subdir)
	write_rc_subdir (e, re, type, name, language, level);
      else
	{
	  if (level == 3)
	    {
	      /* This is the normal case: the three levels are
                 TYPE/NAME/LANGUAGE.  NAME will have been set at level
                 2, and represents the name to use.  We probably just
                 set LANGUAGE, and it will probably match what the
                 resource itself records if anything.  */
	      write_rc_resource (e, type, name, re->u.res, language);
	    }
	  else
	    {
	      wr_printcomment (e, "Resource at unexpected level %d", level);
	      write_rc_resource (e, type, (rc_res_id *) NULL, re->u.res,
				 language);
	    }
	}
    }
  if (rd->entries == NULL)
    {
      wr_print_flush (e);
    }
}