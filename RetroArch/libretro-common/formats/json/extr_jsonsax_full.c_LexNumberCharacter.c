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
typedef  int LexerState ;
typedef  char Codepoint ;

/* Variables and functions */
 char EOF_CODEPOINT ; 
 int LEXER_ERROR ; 
#define  LEXING_NUMBER_AFTER_DOT 139 
#define  LEXING_NUMBER_AFTER_E 138 
#define  LEXING_NUMBER_AFTER_EXPONENT_SIGN 137 
#define  LEXING_NUMBER_AFTER_LEADING_NEGATIVE_ZERO 136 
#define  LEXING_NUMBER_AFTER_LEADING_ZERO 135 
#define  LEXING_NUMBER_AFTER_MINUS 134 
#define  LEXING_NUMBER_AFTER_X 133 
#define  LEXING_NUMBER_DECIMAL_DIGITS 132 
#define  LEXING_NUMBER_EXPONENT_DIGITS 131 
#define  LEXING_NUMBER_FRACTIONAL_DIGITS 130 
#define  LEXING_NUMBER_HEX_DIGITS 129 
#define  LEXING_WHITESPACE 128 

__attribute__((used)) static LexerState LexNumberCharacter(LexerState state, Codepoint c)
{
   switch (state)
   {
      case LEXING_WHITESPACE:
         if (c == '-')
            state = LEXING_NUMBER_AFTER_MINUS;
         else if (c == '0')
            state = LEXING_NUMBER_AFTER_LEADING_ZERO;
         else if (c >= '1' && c <= '9')
            state = LEXING_NUMBER_DECIMAL_DIGITS;
         else
            state = LEXER_ERROR;
         break;

      case LEXING_NUMBER_AFTER_MINUS:
         if (c == '0')
            state = LEXING_NUMBER_AFTER_LEADING_NEGATIVE_ZERO;
         else if (c >= '1' && c <= '9')
            state = LEXING_NUMBER_DECIMAL_DIGITS;
         else
            state = LEXER_ERROR;
         break;

      case LEXING_NUMBER_AFTER_LEADING_ZERO:
      case LEXING_NUMBER_AFTER_LEADING_NEGATIVE_ZERO:
         if (c == '.')
            state = LEXING_NUMBER_AFTER_DOT;
         else if (c == 'e' || c == 'E')
            state = LEXING_NUMBER_AFTER_E;
         else if ((c == 'x' || c == 'X') && state == LEXING_NUMBER_AFTER_LEADING_ZERO)
            state = LEXING_NUMBER_AFTER_X;
         else if (c == EOF_CODEPOINT)
            state = LEXING_WHITESPACE;
         else
            state = LEXER_ERROR;
         break;

      case LEXING_NUMBER_AFTER_X:
         if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))
            state = LEXING_NUMBER_HEX_DIGITS;
         else
            state = LEXER_ERROR;
         break;

      case LEXING_NUMBER_HEX_DIGITS:
         if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))
         {
            /* Still LEXING_NUMBER_HEX_DIGITS. */
         }
         else if (c == EOF_CODEPOINT)
            state = LEXING_WHITESPACE;
         else
            state = LEXER_ERROR;
         break;

      case LEXING_NUMBER_DECIMAL_DIGITS:
         if (c >= '0' && c <= '9')
         {
            /* Still LEXING_NUMBER_DECIMAL_DIGITS. */
         }
         else if (c == '.')
            state = LEXING_NUMBER_AFTER_DOT;
         else if (c == 'e' || c == 'E')
            state = LEXING_NUMBER_AFTER_E;
         else if (c == EOF_CODEPOINT)
            state = LEXING_WHITESPACE;
         else
            state = LEXER_ERROR;
         break;

      case LEXING_NUMBER_AFTER_DOT:
         if (c >= '0' && c <= '9')
            state = LEXING_NUMBER_FRACTIONAL_DIGITS;
         else
            state = LEXER_ERROR;
         break;

      case LEXING_NUMBER_FRACTIONAL_DIGITS:
         if (c >= '0' && c <= '9')
         {
            /* Still LEXING_NUMBER_FRACTIONAL_DIGITS. */
         }
         else if (c == 'e' || c == 'E')
            state = LEXING_NUMBER_AFTER_E;
         else if (c == EOF_CODEPOINT)
            state = LEXING_WHITESPACE;
         else
            state = LEXER_ERROR;
         break;

      case LEXING_NUMBER_AFTER_E:
         if (c == '+' || c == '-')
            state = LEXING_NUMBER_AFTER_EXPONENT_SIGN;
         else if (c >= '0' && c <= '9')
            state = LEXING_NUMBER_EXPONENT_DIGITS;
         else
            state = LEXER_ERROR;
         break;

      case LEXING_NUMBER_AFTER_EXPONENT_SIGN:
         if (c >= '0' && c <= '9')
            state = LEXING_NUMBER_EXPONENT_DIGITS;
         else
            state = LEXER_ERROR;
         break;

      case LEXING_NUMBER_EXPONENT_DIGITS:
         if (c >= '0' && c <= '9')
         {
            /* Still LEXING_NUMBER_EXPONENT_DIGITS. */
         }
         else if (c == EOF_CODEPOINT)
            state = LEXING_WHITESPACE;
         else
            state = LEXER_ERROR;
         break;
   }
   return state;
}