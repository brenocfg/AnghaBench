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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  byte ;
typedef  int Encoding ;
typedef  int Codepoint ;

/* Variables and functions */
 int BOTTOM_6_BITS (int) ; 
 int FIRST_2_BYTE_UTF8_CODEPOINT ; 
 int FIRST_3_BYTE_UTF8_CODEPOINT ; 
 int FIRST_4_BYTE_UTF8_CODEPOINT ; 
 int FIRST_NON_BMP_CODEPOINT ; 
#define  JSON_UTF16BE 132 
#define  JSON_UTF16LE 131 
#define  JSON_UTF32BE 130 
#define  JSON_UTF32LE 129 
#define  JSON_UTF8 128 
 int SURROGATES_FROM_CODEPOINT (int) ; 

__attribute__((used)) static size_t EncodeCodepoint(Codepoint c, Encoding encoding, byte* pBytes)
{
   size_t length = 0;
   switch (encoding)
   {
      case JSON_UTF8:
         if (c < FIRST_2_BYTE_UTF8_CODEPOINT)
         {
            pBytes[0] = (byte)c;
            length = 1;
         }
         else if (c < FIRST_3_BYTE_UTF8_CODEPOINT)
         {
            pBytes[0] = (byte)(0xC0 | (c >> 6));
            pBytes[1] = (byte)(0x80 | BOTTOM_6_BITS(c));
            length = 2;
         }
         else if (c < FIRST_4_BYTE_UTF8_CODEPOINT)
         {
            pBytes[0] = (byte)(0xE0 | (c >> 12));
            pBytes[1] = (byte)(0x80 | BOTTOM_6_BITS(c >> 6));
            pBytes[2] = (byte)(0x80 | BOTTOM_6_BITS(c));
            length = 3;
         }
         else
         {
            pBytes[0] = (byte)(0xF0 | (c >> 18));
            pBytes[1] = (byte)(0x80 | BOTTOM_6_BITS(c >> 12));
            pBytes[2] = (byte)(0x80 | BOTTOM_6_BITS(c >> 6));
            pBytes[3] = (byte)(0x80 | BOTTOM_6_BITS(c));
            length = 4;
         }
         break;

      case JSON_UTF16LE:
         if (c < FIRST_NON_BMP_CODEPOINT)
         {
            pBytes[0] = (byte)(c);
            pBytes[1] = (byte)(c >> 8);
            length = 2;
         }
         else
         {
            uint32_t surrogates = SURROGATES_FROM_CODEPOINT(c);

            /* Leading surrogate. */
            pBytes[0] = (byte)(surrogates >> 16);
            pBytes[1] = (byte)(surrogates >> 24);

            /* Trailing surrogate. */
            pBytes[2] = (byte)(surrogates);
            pBytes[3] = (byte)(surrogates >> 8);
            length = 4;
         }
         break;

      case JSON_UTF16BE:
         if (c < FIRST_NON_BMP_CODEPOINT)
         {
            pBytes[1] = (byte)(c);
            pBytes[0] = (byte)(c >> 8);
            length = 2;
         }
         else
         {
            /* The codepoint requires a surrogate pair in UTF-16. */
            uint32_t surrogates = SURROGATES_FROM_CODEPOINT(c);

            /* Leading surrogate. */
            pBytes[1] = (byte)(surrogates >> 16);
            pBytes[0] = (byte)(surrogates >> 24);

            /* Trailing surrogate. */
            pBytes[3] = (byte)(surrogates);
            pBytes[2] = (byte)(surrogates >> 8);
            length = 4;
         }
         break;

      case JSON_UTF32LE:
         pBytes[0] = (byte)(c);
         pBytes[1] = (byte)(c >> 8);
         pBytes[2] = (byte)(c >> 16);
         pBytes[3] = (byte)(c >> 24);
         length = 4;
         break;

      case JSON_UTF32BE:
         pBytes[3] = (byte)(c);
         pBytes[2] = (byte)(c >> 8);
         pBytes[1] = (byte)(c >> 16);
         pBytes[0] = (byte)(c >> 24);
         length = 4;
         break;
   }
   return length;
}