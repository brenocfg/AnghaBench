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
struct ui_file {int dummy; } ;
struct type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_FIELD_NAME (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_FIELD_TYPE (struct type*,int) ; 
 int TYPE_NFIELDS (struct type*) ; 
 int /*<<< orphan*/  ada_print_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ui_file*,int,int) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 

__attribute__((used)) static void
print_unchecked_union_type (struct type *type, struct ui_file *stream,
			    int show, int level)
{
  fprintf_filtered (stream, "record (?) is");

  if (show < 0)
    fprintf_filtered (stream, " ... end record");
  else if (TYPE_NFIELDS (type) == 0)
    fprintf_filtered (stream, " null; end record");
  else
    {
      int i;

      fprintf_filtered (stream, "\n%*scase ? is", level + 4, "");

      for (i = 0; i < TYPE_NFIELDS (type); i += 1)
	{
	  fprintf_filtered (stream, "\n%*swhen ? =>\n%*s", level + 8, "",
			    level + 12, "");
	  ada_print_type (TYPE_FIELD_TYPE (type, i),
			  TYPE_FIELD_NAME (type, i),
			  stream, show - 1, level + 12);
	  fprintf_filtered (stream, ";");
	}

      fprintf_filtered (stream, "\n%*send case;\n%*send record",
			level + 4, "", level, "");
    }
}