#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ (* encodingDetectedHandler ) (TYPE_1__*) ;} ;
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  TYPE_1__* JSON_Parser ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_Error_AbortedByHandler ; 
 int /*<<< orphan*/  JSON_Failure ; 
 scalar_t__ JSON_Parser_Continue ; 
 int /*<<< orphan*/  JSON_Parser_SetErrorAtCodepoint (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JSON_Success ; 
 scalar_t__ stub1 (TYPE_1__*) ; 

__attribute__((used)) static JSON_Status JSON_Parser_CallEncodingDetectedHandler(JSON_Parser parser)
{
   if (parser->encodingDetectedHandler && parser->encodingDetectedHandler(parser) != JSON_Parser_Continue)
   {
      JSON_Parser_SetErrorAtCodepoint(parser, JSON_Error_AbortedByHandler);
      return JSON_Failure;
   }
   return JSON_Success;
}