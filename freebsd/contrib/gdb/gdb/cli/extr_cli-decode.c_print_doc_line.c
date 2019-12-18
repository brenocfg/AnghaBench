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
 scalar_t__ islower (char) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char toupper (char) ; 
 int /*<<< orphan*/  ui_out_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uiout ; 
 int /*<<< orphan*/  xfree (char*) ; 
 scalar_t__ xmalloc (int) ; 

void
print_doc_line (struct ui_file *stream, char *str)
{
  static char *line_buffer = 0;
  static int line_size;
  char *p;

  if (!line_buffer)
    {
      line_size = 80;
      line_buffer = (char *) xmalloc (line_size);
    }

  p = str;
  while (*p && *p != '\n' && *p != '.' && *p != ',')
    p++;
  if (p - str > line_size - 1)
    {
      line_size = p - str + 1;
      xfree (line_buffer);
      line_buffer = (char *) xmalloc (line_size);
    }
  strncpy (line_buffer, str, p - str);
  line_buffer[p - str] = '\0';
  if (islower (line_buffer[0]))
    line_buffer[0] = toupper (line_buffer[0]);
  ui_out_text (uiout, line_buffer);
}