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
struct TYPE_6__ {scalar_t__ tokenBytesUsed; scalar_t__ tokenAttributes; int /*<<< orphan*/  token; scalar_t__ lexerBits; int /*<<< orphan*/  lexerState; int /*<<< orphan*/  memorySuite; int /*<<< orphan*/  grammarianData; } ;
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  TYPE_1__* JSON_Parser ;
typedef  int /*<<< orphan*/  GrammarianOutput ;

/* Variables and functions */
#define  ACCEPTED_TOKEN 130 
 int /*<<< orphan*/  GRAMMARIAN_EVENT (int /*<<< orphan*/ ) ; 
 int GRAMMARIAN_RESULT_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Grammarian_ProcessToken (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JSON_Error_OutOfMemory ; 
 int /*<<< orphan*/  JSON_Error_UnexpectedToken ; 
 int /*<<< orphan*/  JSON_Failure ; 
 int /*<<< orphan*/  JSON_Parser_HandleGrammarEvents (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JSON_Parser_SetErrorAtCodepoint (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JSON_Parser_SetErrorAtToken (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JSON_Success ; 
 int /*<<< orphan*/  LEXING_WHITESPACE ; 
#define  REJECTED_TOKEN 129 
#define  SYMBOL_STACK_FULL 128 
 int /*<<< orphan*/  T_NONE ; 

__attribute__((used)) static JSON_Status JSON_Parser_ProcessToken(JSON_Parser parser)
{
   GrammarianOutput output;
   output = Grammarian_ProcessToken(&parser->grammarianData, parser->token, &parser->memorySuite);
   switch (GRAMMARIAN_RESULT_CODE(output))
   {
      case ACCEPTED_TOKEN:
         if (!JSON_Parser_HandleGrammarEvents(parser, GRAMMARIAN_EVENT(output)))
            return JSON_Failure;
         break;

      case REJECTED_TOKEN:
         JSON_Parser_SetErrorAtToken(parser, JSON_Error_UnexpectedToken);
         return JSON_Failure;

      case SYMBOL_STACK_FULL:
         JSON_Parser_SetErrorAtCodepoint(parser, JSON_Error_OutOfMemory);
         return JSON_Failure;
   }

   /* Reset the lexer to prepare for the next token. */
   parser->lexerState = LEXING_WHITESPACE;
   parser->lexerBits = 0;
   parser->token = T_NONE;
   parser->tokenAttributes = 0;
   parser->tokenBytesUsed = 0;
   return JSON_Success;
}