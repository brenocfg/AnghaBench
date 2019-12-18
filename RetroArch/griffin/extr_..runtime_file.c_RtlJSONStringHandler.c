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
struct TYPE_2__ {scalar_t__* current_entry_val; } ;
typedef  TYPE_1__ RtlJSONContext ;
typedef  int /*<<< orphan*/  JSON_StringAttributes ;
typedef  int /*<<< orphan*/  JSON_Parser_HandlerResult ;
typedef  int /*<<< orphan*/  JSON_Parser ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_Parser_Continue ; 
 scalar_t__ JSON_Parser_GetUserData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ strdup (char*) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 

__attribute__((used)) static JSON_Parser_HandlerResult RtlJSONStringHandler(JSON_Parser parser, char *pValue, size_t length, JSON_StringAttributes attributes)
{
   RtlJSONContext *pCtx = (RtlJSONContext*)JSON_Parser_GetUserData(parser);
   (void)attributes; /* unused */
   
   if (pCtx->current_entry_val && length && !string_is_empty(pValue))
   {
      if (*pCtx->current_entry_val)
         free(*pCtx->current_entry_val);
      
      *pCtx->current_entry_val = strdup(pValue);
   }
   /* ignore unknown members */
   
   pCtx->current_entry_val = NULL;
   
   return JSON_Parser_Continue;
}