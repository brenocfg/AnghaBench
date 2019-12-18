#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  char byte ;
typedef  int /*<<< orphan*/  WriteBufferData ;
struct TYPE_9__ {int outputEncoding; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__* JSON_Writer ;
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  int /*<<< orphan*/  Encoding ;
typedef  int DecoderResultCode ;
typedef  int /*<<< orphan*/  DecoderOutput ;
typedef  int /*<<< orphan*/  DecoderData ;
typedef  char Codepoint ;

/* Variables and functions */
 char DECODER_CODEPOINT (int /*<<< orphan*/ ) ; 
 int DECODER_RESULT_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Decoder_ProcessByte (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const) ; 
 int /*<<< orphan*/  Decoder_Reset (int /*<<< orphan*/ *) ; 
 scalar_t__ Decoder_SequencePending (int /*<<< orphan*/ *) ; 
 scalar_t__ GET_FLAGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JSON_Error_InvalidEncodingSequence ; 
 int /*<<< orphan*/  JSON_Failure ; 
 int /*<<< orphan*/  JSON_Success ; 
 char JSON_Writer_GetCodepointEscapeCharacter (TYPE_1__*,char) ; 
 int /*<<< orphan*/  JSON_Writer_SetError (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char REPLACEMENT_CHARACTER_CODEPOINT ; 
#define  SEQUENCE_COMPLETE 131 
#define  SEQUENCE_INVALID_EXCLUSIVE 130 
#define  SEQUENCE_INVALID_INCLUSIVE 129 
#define  SEQUENCE_PENDING 128 
 int /*<<< orphan*/  SHORTEST_ENCODING_SEQUENCE (int) ; 
 int /*<<< orphan*/  WRITER_REPLACE_INVALID ; 
 scalar_t__ WriteBuffer_Flush (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  WriteBuffer_Reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteBuffer_WriteBytes (int /*<<< orphan*/ *,TYPE_1__*,char const*,size_t) ; 
 int /*<<< orphan*/  WriteBuffer_WriteCodepoint (int /*<<< orphan*/ *,TYPE_1__*,char) ; 
 int /*<<< orphan*/  WriteBuffer_WriteHexEscapeSequence (int /*<<< orphan*/ *,TYPE_1__*,char) ; 

__attribute__((used)) static JSON_Status JSON_Writer_OutputString(JSON_Writer writer, const byte* pBytes, size_t length, Encoding encoding)
{
   static const byte quoteUTF[] = { 0, 0, 0, '"', 0, 0, 0 };
   static const byte* const quoteEncodings[5] = { quoteUTF + 3, quoteUTF + 3, quoteUTF + 2, quoteUTF + 3, quoteUTF };

   const byte* pQuoteEncoded = quoteEncodings[writer->outputEncoding - 1];
   size_t minSequenceLength = (size_t)SHORTEST_ENCODING_SEQUENCE(writer->outputEncoding);
   DecoderData decoderData;
   WriteBufferData bufferData;
   size_t i = 0;

   WriteBuffer_Reset(&bufferData);

   /* Start quote. */
   if (!WriteBuffer_WriteBytes(&bufferData, writer, pQuoteEncoded, minSequenceLength))
      return JSON_Failure;

   /* String contents. */
   Decoder_Reset(&decoderData);
   while (i < length)
   {
      DecoderOutput output = Decoder_ProcessByte(&decoderData, encoding, pBytes[i]);
      DecoderResultCode result = DECODER_RESULT_CODE(output);
      Codepoint c;
      Codepoint escapeCharacter;
      switch (result)
      {
         case SEQUENCE_PENDING:
            i++;
            break;

         case SEQUENCE_COMPLETE:
            c = DECODER_CODEPOINT(output);
            escapeCharacter = JSON_Writer_GetCodepointEscapeCharacter(writer, c);
            switch (escapeCharacter)
            {
               case 0:
                  /* Output the codepoint as a normal encoding sequence. */
                  if (!WriteBuffer_WriteCodepoint(&bufferData, writer, c))
                     return JSON_Failure;
                  break;

               case 'u':
                  /* Output the codepoint as 1 or 2 hex escape sequences. */
                  if (!WriteBuffer_WriteHexEscapeSequence(&bufferData, writer, c))
                     return JSON_Failure;
                  break;

               default:
                  /* Output the codepoint as a simple escape sequence. */
                  if (!WriteBuffer_WriteCodepoint(&bufferData, writer, '\\') ||
                        !WriteBuffer_WriteCodepoint(&bufferData, writer, escapeCharacter))
                     return JSON_Failure;
                  break;
            }
            i++;
            break;

         case SEQUENCE_INVALID_INCLUSIVE:
            i++;
            /* fallthrough */
         case SEQUENCE_INVALID_EXCLUSIVE:
            if (GET_FLAGS(writer->flags, WRITER_REPLACE_INVALID))
            {
               if (!WriteBuffer_WriteHexEscapeSequence(&bufferData, writer, REPLACEMENT_CHARACTER_CODEPOINT))
                  return JSON_Failure;
            }
            else
            {
               /* Output whatever valid bytes we've accumulated before failing. */
               if (WriteBuffer_Flush(&bufferData, writer))
                  JSON_Writer_SetError(writer, JSON_Error_InvalidEncodingSequence);
               return JSON_Failure;
            }
            break;
      }
   }
   if (Decoder_SequencePending(&decoderData))
   {
      if (GET_FLAGS(writer->flags, WRITER_REPLACE_INVALID))
      {
         if (!WriteBuffer_WriteHexEscapeSequence(&bufferData, writer, REPLACEMENT_CHARACTER_CODEPOINT))
            return JSON_Failure;
      }
      else
      {
         /* Output whatever valid bytes we've accumulated before failing. */
         if (WriteBuffer_Flush(&bufferData, writer))
            JSON_Writer_SetError(writer, JSON_Error_InvalidEncodingSequence);
         return JSON_Failure;
      }
   }

   /* End quote. */
   if (!WriteBuffer_WriteBytes(&bufferData, writer, pQuoteEncoded, minSequenceLength) ||
         !WriteBuffer_Flush(&bufferData, writer))
      return JSON_Failure;
   return JSON_Success;
}