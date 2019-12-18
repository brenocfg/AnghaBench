#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t size; TYPE_1__* list; } ;
typedef  TYPE_2__ file_list_t ;
struct TYPE_5__ {char* alt; char* path; } ;

/* Variables and functions */
 int /*<<< orphan*/  file_list_get_label_at_offset (TYPE_2__ const*,size_t,char const**) ; 
 scalar_t__ strcasestr (char const*,char const*) ; 

bool file_list_search(const file_list_t *list, const char *needle, size_t *idx)
{
   size_t i;
   bool ret        = false;

   if (!list)
      return false;

   for (i = 0; i < list->size; i++)
   {
      const char *str = NULL;
      const char *alt = list->list[i].alt 
            ? list->list[i].alt 
            : list->list[i].path;

      if (!alt)
      {
         file_list_get_label_at_offset(list, i, &alt);
         if (!alt)
            continue;
      }

      str = (const char *)strcasestr(alt, needle);
      if (str == alt)
      {
         /* Found match with first chars, best possible match. */
         *idx = i;
         ret  = true;
         break;
      }
      else if (str && !ret)
      {
         /* Found mid-string match, but try to find a match with
          * first characters before we settle. */
         *idx = i;
         ret  = true;
      }
   }

   return ret;
}