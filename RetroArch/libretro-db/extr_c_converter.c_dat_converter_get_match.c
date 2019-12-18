#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ hash; struct TYPE_13__* next; int /*<<< orphan*/  value; } ;
typedef  TYPE_4__ dat_converter_match_key_t ;
struct TYPE_14__ {scalar_t__ type; int count; TYPE_3__* values; } ;
typedef  TYPE_5__ dat_converter_list_t ;
struct TYPE_10__ {char const* string; TYPE_5__* list; } ;
struct TYPE_11__ {scalar_t__ hash; scalar_t__ type; TYPE_1__ value; int /*<<< orphan*/  key; } ;
struct TYPE_12__ {TYPE_2__ map; } ;

/* Variables and functions */
 scalar_t__ DAT_CONVERTER_MAP_LIST ; 
 scalar_t__ DAT_CONVERTER_STRING_MAP ; 
 int /*<<< orphan*/  retro_assert (TYPE_4__*) ; 
 TYPE_4__* string_is_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char* dat_converter_get_match(
      dat_converter_list_t* list,
      dat_converter_match_key_t* match_key)
{
   int i;

   retro_assert(match_key);

   if (list->type != DAT_CONVERTER_MAP_LIST)
      return NULL;

   for (i = 0; i < list->count; i++)
   {
      if (list->values[i].map.hash == match_key->hash)
      {
         retro_assert(string_is_equal(list->values[i].map.key, match_key->value));

         if (match_key->next)
            return dat_converter_get_match(
                  list->values[i].map.value.list, match_key->next);

         if ((list->values[i].map.type == DAT_CONVERTER_STRING_MAP))
            return list->values[i].map.value.string;

         return NULL;

      }
   }
   return NULL;
}