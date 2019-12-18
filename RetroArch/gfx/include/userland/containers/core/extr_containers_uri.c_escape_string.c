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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  RESERVED_CHARS_TABLE_T ;

/* Variables and functions */
 scalar_t__ URI_RESERVED (char,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 char to_hex (char) ; 

__attribute__((used)) static uint32_t escape_string( const char *str, char *escaped,
      RESERVED_CHARS_TABLE_T reserved )
{
   uint32_t ii;
   uint32_t esclen = 0;

   if (!str)
      return 0;

   for (ii = strlen(str); ii > 0; ii--)
   {
      char c = *str++;

      if (URI_RESERVED(c, reserved))
      {
         escaped[esclen++] = '%';
         escaped[esclen++] = to_hex((c >> 4) & 0xF);
         escaped[esclen++] = to_hex(c & 0xF);
      } else {
         escaped[esclen++] = c;
      }
   }

   return esclen;
}