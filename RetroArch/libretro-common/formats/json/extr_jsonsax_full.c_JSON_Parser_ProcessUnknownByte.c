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
typedef  int uint32_t ;
typedef  int byte ;
struct TYPE_8__ {int state; int bits; } ;
struct TYPE_7__ {TYPE_6__ decoderData; void* inputEncoding; } ;
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  TYPE_1__* JSON_Parser ;

/* Variables and functions */
#define  DECODED_1_OF_4 131 
#define  DECODED_2_OF_4 130 
#define  DECODED_3_OF_4 129 
#define  DECODER_RESET 128 
 int /*<<< orphan*/  Decoder_Reset (TYPE_6__*) ; 
 int /*<<< orphan*/  JSON_Failure ; 
 int /*<<< orphan*/  JSON_Parser_CallEncodingDetectedHandler (TYPE_1__*) ; 
 int /*<<< orphan*/  JSON_Parser_HandleInvalidEncodingSequence (TYPE_1__*,int) ; 
 int /*<<< orphan*/  JSON_Parser_ProcessInputBytes (TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  JSON_Success ; 
 void* JSON_UTF16BE ; 
 void* JSON_UTF16LE ; 
 void* JSON_UTF32BE ; 
 void* JSON_UTF32LE ; 
 void* JSON_UTF8 ; 
 void* JSON_UnknownEncoding ; 
 int LONGEST_ENCODING_SEQUENCE ; 

__attribute__((used)) static JSON_Status JSON_Parser_ProcessUnknownByte(JSON_Parser parser, byte b)
{
   /* When the input encoding is unknown, the first 4 bytes of input are
      recorded in decoder.bits. */
   byte bytes[LONGEST_ENCODING_SEQUENCE];

   switch (parser->decoderData.state)
   {
      case DECODER_RESET:
         parser->decoderData.state = DECODED_1_OF_4;
         parser->decoderData.bits = (uint32_t)b << 24;
         break;

      case DECODED_1_OF_4:
         parser->decoderData.state = DECODED_2_OF_4;
         parser->decoderData.bits |= (uint32_t)b << 16;
         break;

      case DECODED_2_OF_4:
         parser->decoderData.state = DECODED_3_OF_4;
         parser->decoderData.bits |= (uint32_t)b << 8;
         break;

      case DECODED_3_OF_4:
         bytes[0] = (byte)(parser->decoderData.bits >> 24);
         bytes[1] = (byte)(parser->decoderData.bits >> 16);
         bytes[2] = (byte)(parser->decoderData.bits >> 8);
         bytes[3] = (byte)(b);

         /* We try to match the following patterns in order, where .. is any
            byte value and nz is any non-zero byte value:
            EF BB BF .. => UTF-8 with BOM
            FF FE 00 00 => UTF-32LE with BOM
            FF FE nz 00 => UTF-16LE with BOM
            00 00 FE FF -> UTF-32BE with BOM
            FE FF .. .. => UTF-16BE with BOM
            nz nz .. .. => UTF-8
            nz 00 nz .. => UTF-16LE
            nz 00 00 00 => UTF-32LE
            00 nz .. .. => UTF-16BE
            00 00 00 nz => UTF-32BE
            .. .. .. .. => unknown encoding */
         if (bytes[0] == 0xEF && bytes[1] == 0xBB && bytes[2] == 0xBF)
         {
            /* EF BB BF .. */
            parser->inputEncoding = JSON_UTF8;
         }
         else if (bytes[0] == 0xFF && bytes[1] == 0xFE && bytes[3] == 0x00)
         {
            /* FF FE 00 00 or
               FF FE nz 00 */
            parser->inputEncoding = (bytes[2] == 0x00) ? JSON_UTF32LE : JSON_UTF16LE;
         }
         else if (bytes[0] == 0x00 && bytes[1] == 0x00 && bytes[2] == 0xFE && bytes[3] == 0xFF)
         {
            /* 00 00 FE FF */
            parser->inputEncoding = JSON_UTF32BE;
         }
         else if (bytes[0] == 0xFE && bytes[1] == 0xFF)
         {
            /* FE FF .. .. */
            parser->inputEncoding = JSON_UTF16BE;
         }
         else if (bytes[0] != 0x00)
         {
            /* nz .. .. .. */
            if (bytes[1] != 0x00)
            {
               /* nz nz .. .. */
               parser->inputEncoding = JSON_UTF8;
            }
            else if (bytes[2] != 0x00)
            {
               /* nz 00 nz .. */
               parser->inputEncoding = JSON_UTF16LE;
            }
            else if (bytes[3] == 0x00)
            {
               /* nz 00 00 00 */
               parser->inputEncoding = JSON_UTF32LE;
            }
            else
            {
               /* nz 00 00 nz => error */
            }
         }
         else if (bytes[1] != 0x00)
         {
            /* 00 nz .. .. */
            parser->inputEncoding = JSON_UTF16BE;
         }
         else if (bytes[2] == 0x00 && bytes[3] != 0x00)
         {
            /* 00 00 00 nz */
            parser->inputEncoding = JSON_UTF32BE;
         }
         else
         {
            /* 00 00 nz .. or
               00 00 00 00 => error */
         }

         if (parser->inputEncoding == JSON_UnknownEncoding)
            return JSON_Parser_HandleInvalidEncodingSequence(parser, 4);

         if (!JSON_Parser_CallEncodingDetectedHandler(parser))
            return JSON_Failure;

         /* Reset the decoder before reprocessing the bytes. */
         Decoder_Reset(&parser->decoderData);
         return JSON_Parser_ProcessInputBytes(parser, bytes, 4);
   }

   /* We don't have 4 bytes yet. */
   return JSON_Success;
}