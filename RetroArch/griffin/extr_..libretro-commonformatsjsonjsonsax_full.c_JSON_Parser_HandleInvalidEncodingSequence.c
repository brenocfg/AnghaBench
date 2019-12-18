#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ token; int /*<<< orphan*/  flags; int /*<<< orphan*/  depth; int /*<<< orphan*/  tokenAttributes; } ;
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  TYPE_1__* JSON_Parser ;

/* Variables and functions */
 scalar_t__ GET_FLAGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JSON_ContainsReplacedCharacter ; 
 int /*<<< orphan*/  JSON_Error_InvalidEncodingSequence ; 
 int /*<<< orphan*/  JSON_Failure ; 
 scalar_t__ JSON_Parser_FlushLexer (TYPE_1__*) ; 
 scalar_t__ JSON_Parser_FlushParser (TYPE_1__*) ; 
 int /*<<< orphan*/  JSON_Parser_ProcessCodepoint (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  JSON_Parser_SetErrorAtCodepoint (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSER_EMBEDDED_DOCUMENT ; 
 int /*<<< orphan*/  PARSER_REPLACE_INVALID ; 
 int /*<<< orphan*/  REPLACEMENT_CHARACTER_CODEPOINT ; 
 int /*<<< orphan*/  SET_FLAGS_ON (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ T_STRING ; 
 int /*<<< orphan*/  TokenAttributes ; 

__attribute__((used)) static JSON_Status JSON_Parser_HandleInvalidEncodingSequence(
      JSON_Parser parser, size_t encodedLength)
{
   if (parser->token == T_STRING && GET_FLAGS(parser->flags, PARSER_REPLACE_INVALID))
   {
      /* Since we're inside a string token, replacing the invalid sequence
         with the Unicode replacement character as requested by the client
         is a viable way to avoid a parse failure. Outside a string token,
         such a replacement would simply trigger JSON_Error_UnknownToken
         when we tried to process the replacement character, so it's less
         confusing to stick with JSON_Error_InvalidEncodingSequence in that
         case. */
      SET_FLAGS_ON(TokenAttributes, parser->tokenAttributes, JSON_ContainsReplacedCharacter);
      return JSON_Parser_ProcessCodepoint(parser, REPLACEMENT_CHARACTER_CODEPOINT, encodedLength);
   }
   else if (!parser->depth && GET_FLAGS(parser->flags, PARSER_EMBEDDED_DOCUMENT))
   {
      /* Since we're parsing the top-level value of an embedded
         document, assume that the invalid encoding sequence we've
         encountered does not actually belong to the document, and
         finish parsing by pretending that we've encountered EOF
         instead of an invalid sequence. If the content is valid,
         this will fail with JSON_Error_StoppedAfterEmbeddedDocument;
         otherwise, it will fail with an appropriate error. */
      return (JSON_Status)(JSON_Parser_FlushLexer(parser) && JSON_Parser_FlushParser(parser));
   }
   JSON_Parser_SetErrorAtCodepoint(parser, JSON_Error_InvalidEncodingSequence);
   return JSON_Failure;
}