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
struct TYPE_6__ {scalar_t__ byte; scalar_t__ column; scalar_t__ line; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {scalar_t__ writer; scalar_t__ parser; } ;
typedef  TYPE_1__ RtlJSONContext ;
typedef  TYPE_2__ JSON_Location ;
typedef  scalar_t__ JSON_Error ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_ErrorString (scalar_t__) ; 
 scalar_t__ JSON_Error_AbortedByHandler ; 
 scalar_t__ JSON_Parser_GetError (scalar_t__) ; 
 int /*<<< orphan*/  JSON_Parser_GetErrorLocation (scalar_t__,TYPE_2__*) ; 
 scalar_t__ JSON_Writer_GetError (scalar_t__) ; 
 int /*<<< orphan*/  RARCH_ERR (char*,int,...) ; 

__attribute__((used)) static void RtlJSONLogError(RtlJSONContext *pCtx)
{
   if (pCtx->parser && JSON_Parser_GetError(pCtx->parser) != JSON_Error_AbortedByHandler)
   {
      JSON_Error error            = JSON_Parser_GetError(pCtx->parser);
      JSON_Location errorLocation = { 0, 0, 0 };

      (void)JSON_Parser_GetErrorLocation(pCtx->parser, &errorLocation);
      RARCH_ERR("Error: Invalid JSON at line %d, column %d (input byte %d) - %s.\n",
            (int)errorLocation.line + 1,
            (int)errorLocation.column + 1,
            (int)errorLocation.byte,
            JSON_ErrorString(error));
   }
   else if (pCtx->writer && JSON_Writer_GetError(pCtx->writer) != JSON_Error_AbortedByHandler)
   {
      RARCH_ERR("Error: could not write output - %s.\n", JSON_ErrorString(JSON_Writer_GetError(pCtx->writer)));
   }
}