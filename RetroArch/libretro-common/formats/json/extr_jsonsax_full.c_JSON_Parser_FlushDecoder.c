#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int byte ;
struct TYPE_8__ {int state; int bits; } ;
struct TYPE_7__ {scalar_t__ inputEncoding; TYPE_6__ decoderData; } ;
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  TYPE_1__* JSON_Parser ;

/* Variables and functions */
#define  DECODED_1_OF_4 130 
#define  DECODED_2_OF_4 129 
#define  DECODED_3_OF_4 128 
 int DECODER_RESET ; 
 int DECODER_STATE_BYTES (int) ; 
 scalar_t__ Decoder_SequencePending (TYPE_6__*) ; 
 int /*<<< orphan*/  JSON_Failure ; 
 int /*<<< orphan*/  JSON_Parser_CallEncodingDetectedHandler (TYPE_1__*) ; 
 int /*<<< orphan*/  JSON_Parser_HandleInvalidEncodingSequence (TYPE_1__*,int) ; 
 int /*<<< orphan*/  JSON_Parser_ProcessInputBytes (TYPE_1__*,int*,size_t) ; 
 int /*<<< orphan*/  JSON_Success ; 
 void* JSON_UTF16BE ; 
 void* JSON_UTF16LE ; 
 void* JSON_UTF8 ; 
 scalar_t__ JSON_UnknownEncoding ; 

__attribute__((used)) static JSON_Status JSON_Parser_FlushDecoder(JSON_Parser parser)
{
   /* If the input was 1, 2, or 3 bytes long, and the input encoding was not
      explicitly specified by the client, we can sometimes make a reasonable
      guess. If the input was 1 or 3 bytes long, the only encoding that could
      possibly be valid JSON is UF-8. If the input was 2 bytes long, we try
      to match the following patterns in order, where .. is any byte value
      and nz is any non-zero byte value:
      FF FE => UTF-16LE with BOM
      FE FF => UTF-16BE with BOM
      nz nz => UTF-8
      nz 00 => UTF-16LE
      00 nz => UTF-16BE
      .. .. => unknown encoding
      */
   if (parser->inputEncoding == JSON_UnknownEncoding &&
         parser->decoderData.state != DECODER_RESET)
   {
      byte bytes[3];
      size_t length = 0;
      bytes[0] = (byte)(parser->decoderData.bits >> 24);
      bytes[1] = (byte)(parser->decoderData.bits >> 16);
      bytes[2] = (byte)(parser->decoderData.bits >> 8);

      switch (parser->decoderData.state)
      {
         case DECODED_1_OF_4:
            parser->inputEncoding = JSON_UTF8;
            length = 1;
            break;

         case DECODED_2_OF_4:
            /* FF FE */
            if (bytes[0] == 0xFF && bytes[1] == 0xFE)
               parser->inputEncoding = JSON_UTF16LE;
            /* FE FF */
            else if (bytes[0] == 0xFE && bytes[1] == 0xFF)
               parser->inputEncoding = JSON_UTF16BE;
            else if (bytes[0] != 0x00)
            {
               /* nz nz or
                  nz 00 */
               parser->inputEncoding = bytes[1] ? JSON_UTF8 : JSON_UTF16LE;
            }
            /* 00 nz */
            else if (bytes[1] != 0x00)
               parser->inputEncoding = JSON_UTF16BE;
            /* 00 00 */
            else
               return JSON_Parser_HandleInvalidEncodingSequence(parser, 2);
            length = 2;
            break;

         case DECODED_3_OF_4:
            parser->inputEncoding = JSON_UTF8;
            length = 3;
            break;
      }

      if (!JSON_Parser_CallEncodingDetectedHandler(parser))
         return JSON_Failure;

      /* Reset the decoder before reprocessing the bytes. */
      parser->decoderData.state = DECODER_RESET;
      parser->decoderData.bits = 0;
      if (!JSON_Parser_ProcessInputBytes(parser, bytes, length))
         return JSON_Failure;
   }

   /* The decoder should be idle when parsing finishes. */
   if (Decoder_SequencePending(&parser->decoderData))
      return JSON_Parser_HandleInvalidEncodingSequence(
            parser, DECODER_STATE_BYTES(parser->decoderData.state));
   return JSON_Success;
}