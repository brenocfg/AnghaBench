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
struct string_list_elem {char* data; int /*<<< orphan*/  attr; } ;
struct string_list {int size; int cap; struct string_list_elem* elems; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (struct string_list*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char const*) ; 

struct string_list *string_list_clone(
      const struct string_list *src)
{
   unsigned i;
   struct string_list_elem *elems = NULL;
   struct string_list *dest       = (struct string_list*)
      calloc(1, sizeof(struct string_list));

   if (!dest)
      return NULL;

   dest->size      = src->size;
   dest->cap       = src->cap;
   if (dest->cap < dest->size)
      dest->cap    = dest->size;

   elems           = (struct string_list_elem*)
      calloc(dest->cap, sizeof(struct string_list_elem));

   if (!elems)
   {
      free(dest);
      return NULL;
   }

   dest->elems            = elems;

   for (i = 0; i < src->size; i++)
   {
      const char *_src    = src->elems[i].data;
      size_t      len     = _src ? strlen(_src) : 0;

      dest->elems[i].data = NULL;
      dest->elems[i].attr = src->elems[i].attr;

      if (len != 0)
      {
         char *result        = (char*)malloc(len + 1);
         strcpy(result, _src);
         dest->elems[i].data = result;
      }
   }

   return dest;
}