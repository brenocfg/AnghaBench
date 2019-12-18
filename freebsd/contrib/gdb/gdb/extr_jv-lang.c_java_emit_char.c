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

/* Variables and functions */
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,unsigned int) ; 
 int /*<<< orphan*/  fputc_filtered (int,struct ui_file*) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 int /*<<< orphan*/  isprint (int) ; 

__attribute__((used)) static void
java_emit_char (int c, struct ui_file *stream, int quoter)
{
  switch (c)
    {
    case '\\':
    case '\'':
      fprintf_filtered (stream, "\\%c", c);
      break;
    case '\b':
      fputs_filtered ("\\b", stream);
      break;
    case '\t':
      fputs_filtered ("\\t", stream);
      break;
    case '\n':
      fputs_filtered ("\\n", stream);
      break;
    case '\f':
      fputs_filtered ("\\f", stream);
      break;
    case '\r':
      fputs_filtered ("\\r", stream);
      break;
    default:
      if (isprint (c))
	fputc_filtered (c, stream);
      else
	fprintf_filtered (stream, "\\u%.4x", (unsigned int) c);
      break;
    }
}