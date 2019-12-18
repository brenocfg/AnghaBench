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
 int /*<<< orphan*/  QUIT ; 
 int TYPE_FIELD_BITPOS (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_FIELD_NAME (struct type*,int) ; 
 int TYPE_NFIELDS (struct type*) ; 
 int /*<<< orphan*/  ada_enum_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fputs_filtered (int /*<<< orphan*/ ,struct ui_file*) ; 
 int /*<<< orphan*/  wrap_here (char*) ; 

__attribute__((used)) static void
print_enum_type (struct type *type, struct ui_file *stream)
{
  int len = TYPE_NFIELDS (type);
  int i, lastval;

  fprintf_filtered (stream, "(");
  wrap_here (" ");

  lastval = 0;
  for (i = 0; i < len; i++)
    {
      QUIT;
      if (i)
	fprintf_filtered (stream, ", ");
      wrap_here ("    ");
      fputs_filtered (ada_enum_name (TYPE_FIELD_NAME (type, i)), stream);
      if (lastval != TYPE_FIELD_BITPOS (type, i))
	{
	  fprintf_filtered (stream, " => %d", TYPE_FIELD_BITPOS (type, i));
	  lastval = TYPE_FIELD_BITPOS (type, i);
	}
      lastval += 1;
    }
  fprintf_filtered (stream, ")");
}