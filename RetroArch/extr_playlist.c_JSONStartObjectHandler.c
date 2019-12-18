#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int object_depth; int array_depth; int capacity_exceeded; TYPE_1__* playlist; int /*<<< orphan*/ * current_entry; scalar_t__ in_items; } ;
struct TYPE_3__ {size_t size; size_t cap; int modified; int /*<<< orphan*/ * entries; } ;
typedef  int /*<<< orphan*/  JSON_Parser_HandlerResult ;
typedef  int /*<<< orphan*/  JSON_Parser ;
typedef  TYPE_2__ JSONContext ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_Parser_Continue ; 
 scalar_t__ JSON_Parser_GetUserData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RARCH_WARN (char*) ; 

__attribute__((used)) static JSON_Parser_HandlerResult JSONStartObjectHandler(JSON_Parser parser)
{
   JSONContext *pCtx = (JSONContext*)JSON_Parser_GetUserData(parser);

   pCtx->object_depth++;

   if (pCtx->in_items && pCtx->object_depth == 2)
   {
      if ((pCtx->array_depth == 1) && !pCtx->capacity_exceeded)
      {
         if (pCtx->playlist->size < pCtx->playlist->cap)
            pCtx->current_entry = &pCtx->playlist->entries[pCtx->playlist->size];
         else
         {
            /* Hit max item limit.
             * Note: We can't just abort here, since there may
             * be more metadata to read at the end of the file... */
            RARCH_WARN("JSON file contains more entries than current playlist capacity. Excess entries will be discarded.\n");
            pCtx->capacity_exceeded = true;
            pCtx->current_entry = NULL;
            /* In addition, since we are discarding excess entries,
             * the playlist must be flagged as being modified
             * (i.e. the playlist is not the same as when it was
             * last saved to disk...) */
            pCtx->playlist->modified = true;
         }
      }
   }

   return JSON_Parser_Continue;
}