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
typedef  enum playlist_thumbnail_mode { ____Placeholder_playlist_thumbnail_mode } playlist_thumbnail_mode ;
typedef  enum playlist_label_display_mode { ____Placeholder_playlist_label_display_mode } playlist_label_display_mode ;
struct TYPE_2__ {int object_depth; int array_depth; int* current_entry_int_val; unsigned int* current_entry_uint_val; int* current_meta_label_display_mode_val; int* current_meta_thumbnail_mode_val; int /*<<< orphan*/ * current_meta_string; scalar_t__ in_items; } ;
typedef  int /*<<< orphan*/  JSON_StringAttributes ;
typedef  int /*<<< orphan*/  JSON_Parser_HandlerResult ;
typedef  int /*<<< orphan*/  JSON_Parser ;
typedef  TYPE_1__ JSONContext ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_Parser_Continue ; 
 scalar_t__ JSON_Parser_GetUserData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static JSON_Parser_HandlerResult JSONNumberHandler(JSON_Parser parser, char *pValue, size_t length, JSON_StringAttributes attributes)
{
   JSONContext *pCtx = (JSONContext*)JSON_Parser_GetUserData(parser);
   (void)attributes; /* unused */

   if (pCtx->in_items && pCtx->object_depth == 2)
   {
      if (pCtx->array_depth == 1)
      {
         if (pCtx->current_entry_int_val && length && !string_is_empty(pValue))
            *pCtx->current_entry_int_val = (int)strtoul(pValue, NULL, 10);
         else if (pCtx->current_entry_uint_val && length && !string_is_empty(pValue))
            *pCtx->current_entry_uint_val = (unsigned)strtoul(pValue, NULL, 10);
         else
         {
            /* must be a value for an unknown member we aren't tracking, skip it */
         }
      }
   }
   else if (pCtx->object_depth == 1)
   {
      if (pCtx->array_depth == 0)
      {
         if (pCtx->current_meta_string && length && !string_is_empty(pValue))
         {
            /* handle any top-level playlist metadata here */
            /*RARCH_LOG("found meta: %s = %s\n", pCtx->current_meta_string, pValue);*/

            free(pCtx->current_meta_string);
            pCtx->current_meta_string = NULL;

            if (pCtx->current_meta_label_display_mode_val)
               *pCtx->current_meta_label_display_mode_val = (enum playlist_label_display_mode)strtoul(pValue, NULL, 10);
            else if (pCtx->current_meta_thumbnail_mode_val)
               *pCtx->current_meta_thumbnail_mode_val = (enum playlist_thumbnail_mode)strtoul(pValue, NULL, 10);
            else
            {
               /* must be a value for an unknown member we aren't tracking, skip it */
            }
         }
      }
   }

   pCtx->current_entry_int_val               = NULL;
   pCtx->current_entry_uint_val              = NULL;
   pCtx->current_meta_label_display_mode_val = NULL;
   pCtx->current_meta_thumbnail_mode_val     = NULL;

   return JSON_Parser_Continue;
}