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
struct string_list {size_t size; TYPE_1__* elems; } ;
struct TYPE_2__ {char const* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlcat (char*,char const*,size_t) ; 
 size_t strlen (char*) ; 

void string_list_join_concat(char *buffer, size_t size,
      const struct string_list *list, const char *delim)
{
   size_t i, len = strlen(buffer);

   buffer += len;
   size   -= len;

   for (i = 0; i < list->size; i++)
   {
      strlcat(buffer, list->elems[i].data, size);
      if ((i + 1) < list->size)
         strlcat(buffer, delim, size);
   }
}