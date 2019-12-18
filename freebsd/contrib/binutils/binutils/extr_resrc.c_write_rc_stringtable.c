#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int rc_uint_type ;
struct TYPE_9__ {TYPE_2__* strings; } ;
typedef  TYPE_3__ rc_stringtable ;
struct TYPE_7__ {int id; } ;
struct TYPE_10__ {TYPE_1__ u; int /*<<< orphan*/  named; } ;
typedef  TYPE_4__ rc_res_id ;
struct TYPE_8__ {scalar_t__ length; int /*<<< orphan*/  string; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  unicode_print_quoted (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
write_rc_stringtable (FILE *e, const rc_res_id *name,
		      const rc_stringtable *stringtable)
{
  rc_uint_type offset;
  int i;

  if (name != NULL && ! name->named)
    offset = (name->u.id - 1) << 4;
  else
    {
      fprintf (e, "/* %s string table name.  */\n",
	       name == NULL ? "Missing" : "Invalid");
      offset = 0;
    }

  fprintf (e, "BEGIN\n");

  for (i = 0; i < 16; i++)
    {
      if (stringtable->strings[i].length != 0)
	{
	  fprintf (e, "  %lu, ", (long) offset + i);
	  unicode_print_quoted (e, stringtable->strings[i].string,
			 stringtable->strings[i].length);
	  fprintf (e, "\n");
	}
    }

  fprintf (e, "END\n");
}