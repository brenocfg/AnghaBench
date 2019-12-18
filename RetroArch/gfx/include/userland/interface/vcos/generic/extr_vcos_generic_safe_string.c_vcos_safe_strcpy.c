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

/* Variables and functions */
 scalar_t__ strlen (char const*) ; 

size_t vcos_safe_strcpy(char *dst, const char *src, size_t dstlen, size_t offset)
{
   if (offset < dstlen)
   {
      const char *p = src;
      char *endp = dst + dstlen -1;

      dst += offset;

      for (; *p!='\0' && dst != endp; dst++, p++)
         *dst = *p;
      *dst = '\0';
   }
   offset += strlen(src);

   return offset;
}