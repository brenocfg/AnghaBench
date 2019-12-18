#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  scalar_t__ (* JSON_Parser_SimpleTokenHandler ) (TYPE_1__*) ;
typedef  scalar_t__ JSON_Parser_HandlerResult ;
typedef  TYPE_1__* JSON_Parser ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_Error_AbortedByHandler ; 
 int /*<<< orphan*/  JSON_Failure ; 
 scalar_t__ JSON_Parser_Continue ; 
 int /*<<< orphan*/  JSON_Parser_SetErrorAtToken (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JSON_Success ; 
 int /*<<< orphan*/  PARSER_IN_TOKEN_HANDLER ; 
 int /*<<< orphan*/  ParserState ; 
 int /*<<< orphan*/  SET_FLAGS_OFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_FLAGS_ON (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static JSON_Status JSON_Parser_CallSimpleTokenHandler(JSON_Parser parser, JSON_Parser_SimpleTokenHandler handler)
{
   if (handler)
   {
      JSON_Parser_HandlerResult result;
      SET_FLAGS_ON(ParserState, parser->state, PARSER_IN_TOKEN_HANDLER);
      result = handler(parser);
      SET_FLAGS_OFF(ParserState, parser->state, PARSER_IN_TOKEN_HANDLER);
      if (result != JSON_Parser_Continue)
      {
         JSON_Parser_SetErrorAtToken(parser, JSON_Error_AbortedByHandler);
         return JSON_Failure;
      }
   }
   return JSON_Success;
}