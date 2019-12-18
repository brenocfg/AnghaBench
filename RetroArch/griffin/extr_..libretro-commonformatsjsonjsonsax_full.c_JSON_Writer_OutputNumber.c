#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  byte ;
typedef  int /*<<< orphan*/  WriteBufferData ;
typedef  scalar_t__ LexerState ;
typedef  int /*<<< orphan*/  JSON_Writer ;
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  int /*<<< orphan*/  Encoding ;
typedef  int DecoderResultCode ;
typedef  int /*<<< orphan*/  DecoderOutput ;
typedef  int /*<<< orphan*/  DecoderData ;
typedef  int /*<<< orphan*/  Codepoint ;

/* Variables and functions */
 int /*<<< orphan*/  DECODER_CODEPOINT (int /*<<< orphan*/ ) ; 
 int DECODER_RESULT_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Decoder_ProcessByte (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  Decoder_Reset (int /*<<< orphan*/ *) ; 
 scalar_t__ Decoder_SequencePending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EOF_CODEPOINT ; 
 int /*<<< orphan*/  JSON_Error_InvalidEncodingSequence ; 
 int /*<<< orphan*/  JSON_Error_InvalidNumber ; 
 int /*<<< orphan*/  JSON_Failure ; 
 int /*<<< orphan*/  JSON_Success ; 
 int /*<<< orphan*/  JSON_Writer_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LEXER_ERROR ; 
 scalar_t__ LEXING_WHITESPACE ; 
 scalar_t__ LexNumberCharacter (scalar_t__,int /*<<< orphan*/ ) ; 
#define  SEQUENCE_COMPLETE 131 
#define  SEQUENCE_INVALID_EXCLUSIVE 130 
#define  SEQUENCE_INVALID_INCLUSIVE 129 
#define  SEQUENCE_PENDING 128 
 scalar_t__ WriteBuffer_Flush (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuffer_Reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteBuffer_WriteCodepoint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static JSON_Status JSON_Writer_OutputNumber(JSON_Writer writer, const byte* pBytes, size_t length, Encoding encoding)
{
   DecoderData decoderData;
   WriteBufferData bufferData;
   LexerState lexerState = LEXING_WHITESPACE;
   size_t i;
   Decoder_Reset(&decoderData);
   WriteBuffer_Reset(&bufferData);
   for (i = 0; i < length; i++)
   {
      DecoderOutput output = Decoder_ProcessByte(&decoderData, encoding, pBytes[i]);
      DecoderResultCode result = DECODER_RESULT_CODE(output);
      Codepoint c;
      switch (result)
      {
         case SEQUENCE_PENDING:
            break;

         case SEQUENCE_COMPLETE:
            c = DECODER_CODEPOINT(output);
            lexerState = LexNumberCharacter(lexerState, c);
            if (lexerState == LEXER_ERROR)
            {
               /* Output whatever valid bytes we've accumulated before failing. */
               if (WriteBuffer_Flush(&bufferData, writer))
                  JSON_Writer_SetError(writer, JSON_Error_InvalidNumber);
               return JSON_Failure;
            }
            if (!WriteBuffer_WriteCodepoint(&bufferData, writer, c))
               return JSON_Failure;
            break;

         case SEQUENCE_INVALID_INCLUSIVE:
         case SEQUENCE_INVALID_EXCLUSIVE:
            /* Output whatever valid bytes we've accumulated before failing. */
            if (WriteBuffer_Flush(&bufferData, writer))
               JSON_Writer_SetError(writer, JSON_Error_InvalidEncodingSequence);
            return JSON_Failure;
      }
   }
   if (!WriteBuffer_Flush(&bufferData, writer))
      return JSON_Failure;
   if (Decoder_SequencePending(&decoderData))
   {
      JSON_Writer_SetError(writer, JSON_Error_InvalidEncodingSequence);
      return JSON_Failure;
   }
   if (LexNumberCharacter(lexerState, EOF_CODEPOINT) == LEXER_ERROR)
   {
      JSON_Writer_SetError(writer, JSON_Error_InvalidNumber);
      return JSON_Failure;
   }
   return JSON_Success;
}