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
struct id {int sequence; char* name; struct id* next; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,int,char*) ; 

__attribute__((used)) static void
write_list_with_asm (FILE *stream, const char *prefix, struct id *list)
{
  while (list)
    {
      fprintf (stream, "%sx%d __asm__ (\"%s\");\n",
	       prefix, list->sequence, list->name);
      list = list->next;
    }
}