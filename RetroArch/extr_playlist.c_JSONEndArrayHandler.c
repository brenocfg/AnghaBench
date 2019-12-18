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
struct TYPE_2__ {int array_depth; int object_depth; int in_items; int in_subsystem_roms; int /*<<< orphan*/ * current_items_string; int /*<<< orphan*/ * current_meta_string; } ;
typedef  int /*<<< orphan*/  JSON_Parser_HandlerResult ;
typedef  int /*<<< orphan*/  JSON_Parser ;
typedef  TYPE_1__ JSONContext ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_Parser_Continue ; 
 scalar_t__ JSON_Parser_GetUserData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  retro_assert (int) ; 
 scalar_t__ string_is_equal (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static JSON_Parser_HandlerResult JSONEndArrayHandler(JSON_Parser parser)
{
   JSONContext *pCtx = (JSONContext*)JSON_Parser_GetUserData(parser);

   retro_assert(pCtx->array_depth > 0);

   pCtx->array_depth--;

   if (pCtx->object_depth == 1)
   {
      if (pCtx->in_items && string_is_equal(pCtx->current_meta_string, "items") && pCtx->array_depth == 0)
      {
         free(pCtx->current_meta_string);
         pCtx->current_meta_string = NULL;
         pCtx->in_items = false;

         if (pCtx->current_items_string)
         {
            free(pCtx->current_items_string);
            pCtx->current_items_string = NULL;
         }
      }
   }
   else if (pCtx->object_depth == 2)
   {
      if (pCtx->in_subsystem_roms && string_is_equal(pCtx->current_items_string, "subsystem_roms") && pCtx->array_depth == 1)
      {
         pCtx->in_subsystem_roms = false;
      }
   }

   return JSON_Parser_Continue;
}