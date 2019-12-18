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
union string_list_elem_attr {int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int object_depth; int array_depth; int /*<<< orphan*/ ** current_meta_val; int /*<<< orphan*/ ** current_entry_val; int /*<<< orphan*/ * current_meta_string; scalar_t__ in_items; scalar_t__* current_entry_string_list_val; scalar_t__ in_subsystem_roms; } ;
typedef  int /*<<< orphan*/  JSON_StringAttributes ;
typedef  int /*<<< orphan*/  JSON_Parser_HandlerResult ;
typedef  int /*<<< orphan*/  JSON_Parser ;
typedef  TYPE_1__ JSONContext ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_Parser_Continue ; 
 scalar_t__ JSON_Parser_GetUserData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 int /*<<< orphan*/  string_list_append (scalar_t__,char*,union string_list_elem_attr) ; 
 scalar_t__ string_list_new () ; 

__attribute__((used)) static JSON_Parser_HandlerResult JSONStringHandler(JSON_Parser parser, char *pValue, size_t length, JSON_StringAttributes attributes)
{
   JSONContext *pCtx = (JSONContext*)JSON_Parser_GetUserData(parser);
   (void)attributes; /* unused */

   if (pCtx->in_items && pCtx->in_subsystem_roms && pCtx->object_depth == 2 && pCtx->array_depth == 2)
   {
      if (pCtx->current_entry_string_list_val && length && !string_is_empty(pValue))
      {
         union string_list_elem_attr attr = {0};

         if (!*pCtx->current_entry_string_list_val)
            *pCtx->current_entry_string_list_val = string_list_new();

         string_list_append(*pCtx->current_entry_string_list_val, pValue, attr);
      }
   }
   else if (pCtx->in_items && pCtx->object_depth == 2)
   {
      if (pCtx->array_depth == 1)
      {
         if (pCtx->current_entry_val && length && !string_is_empty(pValue))
         {
            if (*pCtx->current_entry_val)
               free(*pCtx->current_entry_val);
            *pCtx->current_entry_val = strdup(pValue);
         }
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
         if (pCtx->current_meta_val && length && !string_is_empty(pValue))
         {
            /* handle any top-level playlist metadata here */
            /*RARCH_LOG("found meta: %s = %s\n", pCtx->current_meta_string, pValue);*/

            free(pCtx->current_meta_string);
            pCtx->current_meta_string = NULL;

            if (*pCtx->current_meta_val)
               free(*pCtx->current_meta_val);

            *pCtx->current_meta_val = strdup(pValue);
         }
      }
   }

   pCtx->current_entry_val = NULL;
   pCtx->current_meta_val  = NULL;

   return JSON_Parser_Continue;
}