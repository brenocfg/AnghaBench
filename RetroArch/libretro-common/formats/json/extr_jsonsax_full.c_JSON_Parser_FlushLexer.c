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
struct TYPE_5__ {scalar_t__ lexerState; } ;
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  TYPE_1__* JSON_Parser ;

/* Variables and functions */
 int /*<<< orphan*/  EOF_CODEPOINT ; 
 int /*<<< orphan*/  JSON_Error_IncompleteToken ; 
 int /*<<< orphan*/  JSON_Failure ; 
 int /*<<< orphan*/  JSON_Parser_ProcessCodepoint (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JSON_Parser_SetErrorAtToken (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JSON_Success ; 
 scalar_t__ LEXING_WHITESPACE ; 

__attribute__((used)) static JSON_Status JSON_Parser_FlushLexer(JSON_Parser parser)
{
   /* Push the EOF codepoint to the lexer so that it can finish the pending
      token, if any. The EOF codepoint is never emitted by the decoder
      itself, since it is outside the Unicode range and therefore cannot
      be encoded in any of the possible input encodings. */
   if (!JSON_Parser_ProcessCodepoint(parser, EOF_CODEPOINT, 0))
      return JSON_Failure;

   /* The lexer should be idle when parsing finishes. */
   if (parser->lexerState != LEXING_WHITESPACE)
   {
      JSON_Parser_SetErrorAtToken(parser, JSON_Error_IncompleteToken);
      return JSON_Failure;
   }
   return JSON_Success;
}