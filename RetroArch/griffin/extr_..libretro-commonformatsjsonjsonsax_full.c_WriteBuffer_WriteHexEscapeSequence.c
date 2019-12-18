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
typedef  int /*<<< orphan*/  escapeSequence ;
typedef  char byte ;
typedef  int /*<<< orphan*/  WriteBuffer ;
typedef  int /*<<< orphan*/  JSON_Writer ;
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  int Codepoint ;

/* Variables and functions */
 int FIRST_NON_BMP_CODEPOINT ; 
 int /*<<< orphan*/  JSON_Failure ; 
 int /*<<< orphan*/  JSON_Success ; 
 int SURROGATES_FROM_CODEPOINT (int) ; 
 int /*<<< orphan*/  WriteBuffer_WriteCodepoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static JSON_Status WriteBuffer_WriteHexEscapeSequence(WriteBuffer buffer, JSON_Writer writer, Codepoint c)
{
   if (c >= FIRST_NON_BMP_CODEPOINT)
   {
      /* Non-BMP codepoints must be hex-escaped by escaping the UTF-16
         surrogate pair for the codepoint. We put the leading surrogate
         in the low 16 bits of c so that it gets written first, then
         the second pass through the loop will write out the trailing
         surrogate. x*/
      c = SURROGATES_FROM_CODEPOINT(c);
      c = (c << 16) | (c >> 16);
   }
   do
   {
      static const byte hexDigits[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
      byte escapeSequence[6];
      int i;
      escapeSequence[0] = '\\';
      escapeSequence[1] = 'u';
      escapeSequence[2] = hexDigits[(c >> 12) & 0xF];
      escapeSequence[3] = hexDigits[(c >> 8) & 0xF];
      escapeSequence[4] = hexDigits[(c >> 4) & 0xF];
      escapeSequence[5] = hexDigits[c & 0xF];
      for (i = 0; i < sizeof(escapeSequence); i++)
      {
         if (!WriteBuffer_WriteCodepoint(buffer, writer, escapeSequence[i]))
            return JSON_Failure;
      }
      c >>= 16;
   } while (c);
   return JSON_Success;
}