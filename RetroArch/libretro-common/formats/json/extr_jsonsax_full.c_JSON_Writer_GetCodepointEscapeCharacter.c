#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__* JSON_Writer ;
typedef  int Codepoint ;

/* Variables and functions */
#define  BACKSPACE_CODEPOINT 135 
#define  CARRIAGE_RETURN_CODEPOINT 134 
#define  DELETE_CODEPOINT 133 
 int FIRST_NON_ASCII_CODEPOINT ; 
 int FIRST_NON_CONTROL_CODEPOINT ; 
#define  FORM_FEED_CODEPOINT 132 
 int /*<<< orphan*/  GET_FLAGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_NONCHARACTER (int) ; 
#define  LINE_FEED_CODEPOINT 131 
#define  LINE_SEPARATOR_CODEPOINT 130 
#define  PARAGRAPH_SEPARATOR_CODEPOINT 129 
#define  TAB_CODEPOINT 128 
 int /*<<< orphan*/  WRITER_ESCAPE_NON_ASCII ; 

__attribute__((used)) static Codepoint JSON_Writer_GetCodepointEscapeCharacter(JSON_Writer writer, Codepoint c)
{
   switch (c)
   {
      case BACKSPACE_CODEPOINT:
         return 'b';

      case TAB_CODEPOINT:
         return 't';

      case LINE_FEED_CODEPOINT:
         return 'n';

      case FORM_FEED_CODEPOINT:
         return 'f';

      case CARRIAGE_RETURN_CODEPOINT:
         return 'r';

      case '"':
         return '"';
      /* Don't escape forward slashes */
      /*case '/':
         return '/';*/

      case '\\':
         return '\\';

      case DELETE_CODEPOINT:
      case LINE_SEPARATOR_CODEPOINT:
      case PARAGRAPH_SEPARATOR_CODEPOINT:
         return 'u';

      default:
         if (c < FIRST_NON_CONTROL_CODEPOINT || IS_NONCHARACTER(c) ||
               (GET_FLAGS(writer->flags, WRITER_ESCAPE_NON_ASCII) && c > FIRST_NON_ASCII_CODEPOINT))
            return 'u';
         break;
   }
   return 0;
}