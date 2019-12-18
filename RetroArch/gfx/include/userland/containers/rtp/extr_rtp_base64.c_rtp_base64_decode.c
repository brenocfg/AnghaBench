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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ INVALID ; 
 int /*<<< orphan*/  IN_BASE64_RANGE (char) ; 
 char LOWEST_BASE64_CHAR ; 
 scalar_t__* base64_decode_lookup ; 

uint8_t *rtp_base64_decode(const char *str, uint32_t str_len, uint8_t *buffer, uint32_t buffer_len)
{
   uint32_t character_count = 0;
   uint32_t value = 0;
   uint32_t ii;
   char cc;
   uint8_t lookup;

   /* Build up sets of four characters (ignoring invalid ones) to generate
    * triplets of bytes, until either the end of the string or the pad ('=')
    * characters are reached. */

   for (ii = 0; ii < str_len; ii++)
   {
      cc = *str++;
      if (cc == '=')
         break;         /* Found a pad character: stop */

      if (!IN_BASE64_RANGE(cc))
         continue;      /* Ignore invalid character */

      lookup = base64_decode_lookup[cc - LOWEST_BASE64_CHAR];
      if (lookup == INVALID)
         continue;      /* Ignore invalid character */

      value = (value << 6) | lookup;
      character_count++;

      if (character_count == 4)
      {
         if (buffer_len < 3)
            return NULL;   /* Not enough room in the output buffer */

         *buffer++ = (uint8_t)(value >> 16);
         *buffer++ = (uint8_t)(value >>  8);
         *buffer++ = (uint8_t)(value      );
         buffer_len -= 3;

         character_count = 0;
         value = 0;
      }
   }

   /* If there were extra characters on the end, these need to be handled to get
    * the last one or two bytes. */

   switch (character_count)
   {
   case 0:  /* Nothing more to do, the final bytes were converted in the loop */
      break;
   case 2:  /* One additional byte, padded with four zero bits */
      if (!buffer_len)
         return NULL;
      *buffer++ = (uint8_t)(value >> 4);
      break;
   case 3:  /* Two additional bytes, padded with two zero bits */
      if (buffer_len < 2)
         return NULL;
      *buffer++ = (uint8_t)(value >> 10);
      *buffer++ = (uint8_t)(value >> 2);
      break;
   default: /* This is an invalid Base64 encoding */
      return NULL;
   }

   /* Return number of bytes written to the buffer */
   return buffer;
}