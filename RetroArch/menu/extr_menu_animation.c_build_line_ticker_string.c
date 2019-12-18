#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct string_list {int size; TYPE_1__* elems; } ;
struct TYPE_2__ {char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 

__attribute__((used)) static void build_line_ticker_string(
      size_t num_display_lines, size_t line_offset, struct string_list *lines,
      char *dest_str, size_t dest_str_len)
{
   size_t i;

   for (i = 0; i < num_display_lines; i++)
   {
      size_t offset     = i + line_offset;
      size_t line_index = offset % (lines->size + 1);
      bool line_valid   = true;

      if (line_index >= lines->size)
         line_valid = false;

      if (line_valid)
         strlcat(dest_str, lines->elems[line_index].data, dest_str_len);

      if (i < num_display_lines - 1)
         strlcat(dest_str, "\n", dest_str_len);
   }
}