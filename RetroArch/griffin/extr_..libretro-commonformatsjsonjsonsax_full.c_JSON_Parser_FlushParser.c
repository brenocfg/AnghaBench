#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  grammarianData; } ;
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  TYPE_1__* JSON_Parser ;

/* Variables and functions */
 int /*<<< orphan*/  Grammarian_FinishedDocument (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JSON_Error_ExpectedMoreTokens ; 
 int /*<<< orphan*/  JSON_Failure ; 
 int /*<<< orphan*/  JSON_Parser_SetErrorAtCodepoint (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JSON_Success ; 

__attribute__((used)) static JSON_Status JSON_Parser_FlushParser(JSON_Parser parser)
{
   /* The symbol stack should be empty when parsing finishes. */
   if (!Grammarian_FinishedDocument(&parser->grammarianData))
   {
      JSON_Parser_SetErrorAtCodepoint(parser, JSON_Error_ExpectedMoreTokens);
      return JSON_Failure;
   }
   return JSON_Success;
}