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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 char* strcasestr (char const*,char*) ; 
 char* strstr (char const*,char*) ; 

int string_parse_html_anchor(const char *line, char *link, char *name,
      size_t link_size, size_t name_size)
{
   if (!line || !link || !name)
      return 1;

   memset(link, 0, link_size);
   memset(name, 0, name_size);

   line = strcasestr(line, "<a href=\"");

   if (!line)
      return 1;

   line += 9;

   if (line && *line)
   {
      if (!*link)
      {
         const char *end = strstr(line, "\"");

         if (!end)
            return 1;

         memcpy(link, line, end - line);

         *(link + (end - line)) = '\0';
         line += end - line;
      }

      if (!*name)
      {
         const char *start = strstr(line, "\">");
         const char *end   = start ? strstr(start, "</a>") : NULL;

         if (!start || !end)
            return 1;

         memcpy(name, start + 2, end - start - 2);

         *(name + (end - start - 2)) = '\0';
      }
   }

   return 0;
}