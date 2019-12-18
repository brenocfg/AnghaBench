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
struct excluded_lib {char* name; struct excluded_lib* next; } ;

/* Variables and functions */
 struct excluded_lib* excluded_libs ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 
 char* strpbrk (char const*,char*) ; 
 void* xmalloc (int) ; 

void
add_excluded_libs (const char *list)
{
  const char *p = list, *end;

  while (*p != '\0')
    {
      struct excluded_lib *entry;
      end = strpbrk (p, ",:");
      if (end == NULL)
	end = p + strlen (p);
      entry = xmalloc (sizeof (*entry));
      entry->next = excluded_libs;
      entry->name = xmalloc (end - p + 1);
      memcpy (entry->name, p, end - p);
      entry->name[end - p] = '\0';
      excluded_libs = entry;
      if (*end == '\0')
	break;
      p = end + 1;
    }
}