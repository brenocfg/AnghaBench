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
 int /*<<< orphan*/  fprintf_unfiltered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fputc_unfiltered (int,struct ui_file*) ; 

__attribute__((used)) static void
fputc_readable (int ch, struct ui_file *file)
{
  if (ch == '\n')
    fputc_unfiltered ('\n', file);
  else if (ch == '\r')
    fprintf_unfiltered (file, "\\r");
  else if (ch < 0x20)		/* ASCII control character */
    fprintf_unfiltered (file, "^%c", ch + '@');
  else if (ch >= 0x7f)		/* non-ASCII characters (rubout or greater) */
    fprintf_unfiltered (file, "[%02x]", ch & 0xff);
  else
    fputc_unfiltered (ch, file);
}