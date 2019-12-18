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

/* Variables and functions */
 scalar_t__ INVALID ; 
 int /*<<< orphan*/  IN_BASE64_RANGE (char) ; 
 char LOWEST_BASE64_CHAR ; 
 scalar_t__* base64_decode_lookup ; 

uint32_t rtp_base64_byte_length(const char *str, uint32_t str_len)
{
   uint32_t character_count = 0;
   uint32_t ii;
   char cc;

   /* Scan through string until either a pad ('=') character or the end is
    * reached. Ignore characters that are not part of the Base64 alphabet.
    * Number of bytes should then be 3/4 of the character count. */

   for (ii = 0; ii < str_len; ii++)
   {
      cc = *str++;
      if (cc == '=')
         break;         /* Found a pad character: stop */

      if (!IN_BASE64_RANGE(cc))
         continue;      /* Ignore invalid character */

      if (base64_decode_lookup[cc - LOWEST_BASE64_CHAR] != INVALID)
         character_count++;
   }

   return (character_count * 3) >> 2;
}