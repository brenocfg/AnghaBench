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
struct TYPE_4__ {int tokenBytesLength; int /*<<< orphan*/  state; int /*<<< orphan*/ * arrayItemHandler; int /*<<< orphan*/ * endArrayHandler; int /*<<< orphan*/ * startArrayHandler; int /*<<< orphan*/ * objectMemberHandler; int /*<<< orphan*/ * endObjectHandler; int /*<<< orphan*/ * startObjectHandler; int /*<<< orphan*/ * specialNumberHandler; int /*<<< orphan*/ * numberHandler; int /*<<< orphan*/ * stringHandler; int /*<<< orphan*/ * booleanHandler; int /*<<< orphan*/ * nullHandler; int /*<<< orphan*/ * encodingDetectedHandler; int /*<<< orphan*/  grammarianData; int /*<<< orphan*/  decoderData; int /*<<< orphan*/ * pMemberNames; void* maxNumberLength; void* maxStringLength; scalar_t__ tokenBytesUsed; int /*<<< orphan*/  defaultTokenBytes; int /*<<< orphan*/  pTokenBytes; scalar_t__ depth; scalar_t__ tokenLocationColumn; scalar_t__ tokenLocationLine; scalar_t__ tokenLocationByte; scalar_t__ codepointLocationColumn; scalar_t__ codepointLocationLine; scalar_t__ codepointLocationByte; scalar_t__ lexerBits; int /*<<< orphan*/  lexerState; scalar_t__ errorOffset; int /*<<< orphan*/  error; scalar_t__ tokenAttributes; int /*<<< orphan*/  token; void* numberEncoding; void* stringEncoding; int /*<<< orphan*/  inputEncoding; int /*<<< orphan*/  flags; int /*<<< orphan*/ * userData; } ;
typedef  TYPE_1__* JSON_Parser ;

/* Variables and functions */
 int /*<<< orphan*/  Decoder_Reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Grammarian_Reset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  JSON_Error_None ; 
 int /*<<< orphan*/  JSON_Parser_PopMemberNameList (TYPE_1__*) ; 
 void* JSON_UTF8 ; 
 int /*<<< orphan*/  JSON_UnknownEncoding ; 
 int /*<<< orphan*/  LEXING_WHITESPACE ; 
 int /*<<< orphan*/  PARSER_DEFAULT_FLAGS ; 
 int /*<<< orphan*/  PARSER_RESET ; 
 void* SIZE_MAX ; 
 int /*<<< orphan*/  T_NONE ; 

__attribute__((used)) static void JSON_Parser_ResetData(JSON_Parser parser, int isInitialized)
{
   parser->userData                 = NULL;
   parser->flags                    = PARSER_DEFAULT_FLAGS;
   parser->inputEncoding            = JSON_UnknownEncoding;
   parser->stringEncoding           = JSON_UTF8;
   parser->numberEncoding           = JSON_UTF8;
   parser->token                    = T_NONE;
   parser->tokenAttributes          = 0;
   parser->error                    = JSON_Error_None;
   parser->errorOffset              = 0;
   parser->lexerState               = LEXING_WHITESPACE;
   parser->lexerBits                = 0;
   parser->codepointLocationByte    = 0;
   parser->codepointLocationLine    = 0;
   parser->codepointLocationColumn  = 0;
   parser->tokenLocationByte        = 0;
   parser->tokenLocationLine        = 0;
   parser->tokenLocationColumn      = 0;
   parser->depth                    = 0;

   if (!isInitialized)
   {
      parser->pTokenBytes      = parser->defaultTokenBytes;
      parser->tokenBytesLength = sizeof(parser->defaultTokenBytes);
   }
   else
   {
      /* When we reset the parser, we keep the output buffer and the symbol
         stack that have already been allocated, if any. If the client wants
         to reclaim the memory used by the those buffers, he needs to free
         the parser and create a new one. */
   }
   parser->tokenBytesUsed  = 0;
   parser->maxStringLength = SIZE_MAX;
   parser->maxNumberLength = SIZE_MAX;
   if (!isInitialized)
      parser->pMemberNames = NULL;
   else
   {
      while (parser->pMemberNames)
         JSON_Parser_PopMemberNameList(parser);
   }
   Decoder_Reset(&parser->decoderData);
   Grammarian_Reset(&parser->grammarianData, isInitialized);
   parser->encodingDetectedHandler = NULL;
   parser->nullHandler = NULL;
   parser->booleanHandler = NULL;
   parser->stringHandler = NULL;
   parser->numberHandler = NULL;
   parser->specialNumberHandler = NULL;
   parser->startObjectHandler = NULL;
   parser->endObjectHandler = NULL;
   parser->objectMemberHandler = NULL;
   parser->startArrayHandler = NULL;
   parser->endArrayHandler = NULL;
   parser->arrayItemHandler = NULL;
   parser->state = PARSER_RESET; /* do this last! */
}