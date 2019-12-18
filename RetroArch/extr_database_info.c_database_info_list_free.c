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
struct TYPE_5__ {struct TYPE_5__* md5; struct TYPE_5__* sha1; struct TYPE_5__* bbfc_rating; struct TYPE_5__* esrb_rating; struct TYPE_5__* elspa_rating; struct TYPE_5__* enhancement_hw; struct TYPE_5__* pegi_rating; struct TYPE_5__* cero_rating; struct TYPE_5__* edge_magazine_review; struct TYPE_5__* franchise; struct TYPE_5__* origin; int /*<<< orphan*/ * developer; struct TYPE_5__* publisher; struct TYPE_5__* description; struct TYPE_5__* genre; struct TYPE_5__* serial; struct TYPE_5__* rom_name; struct TYPE_5__* name; } ;
typedef  TYPE_1__ database_info_t ;
struct TYPE_6__ {size_t count; TYPE_1__* list; } ;
typedef  TYPE_2__ database_info_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  string_list_free (int /*<<< orphan*/ *) ; 

void database_info_list_free(database_info_list_t *database_info_list)
{
   size_t i;

   if (!database_info_list)
      return;

   for (i = 0; i < database_info_list->count; i++)
   {
      database_info_t *info = &database_info_list->list[i];

      if (info->name)
         free(info->name);
      if (info->rom_name)
         free(info->rom_name);
      if (info->serial)
         free(info->serial);
      if (info->genre)
         free(info->genre);
      if (info->description)
         free(info->description);
      if (info->publisher)
         free(info->publisher);
      if (info->developer)
         string_list_free(info->developer);
      info->developer = NULL;
      if (info->origin)
         free(info->origin);
      if (info->franchise)
         free(info->franchise);
      if (info->edge_magazine_review)
         free(info->edge_magazine_review);

      if (info->cero_rating)
         free(info->cero_rating);
      if (info->pegi_rating)
         free(info->pegi_rating);
      if (info->enhancement_hw)
         free(info->enhancement_hw);
      if (info->elspa_rating)
         free(info->elspa_rating);
      if (info->esrb_rating)
         free(info->esrb_rating);
      if (info->bbfc_rating)
         free(info->bbfc_rating);
      if (info->sha1)
         free(info->sha1);
      if (info->md5)
         free(info->md5);
   }

   free(database_info_list->list);
}