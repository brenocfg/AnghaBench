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
 unsigned int htonl (unsigned int) ; 
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ islower (unsigned char) ; 
 int /*<<< orphan*/  isspace (unsigned char) ; 
 scalar_t__ isxdigit (unsigned char) ; 

int rtinet_aton(const char *cp, unsigned int *addr)
{
	unsigned int 	val;
	int         	base, n;
	char        	c;
	unsigned int    parts[4];
	unsigned int    *pp = parts;

	for (;;)
    {
         /*
          * Collect number up to ``.''.
          * Values are specified as for C:
          *	0x=hex, 0=octal, other=decimal.
          */
         val = 0;
         base = 10;
         if (*cp == '0')
         {
             if (*++cp == 'x' || *cp == 'X')
                 base = 16, cp++;
             else
                 base = 8;
         }
         while ((c = *cp) != '\0')
         {
             if (isdigit((unsigned char) c))
             {
                 val = (val * base) + (c - '0');
                 cp++;
                 continue;
             }
             if (base == 16 && isxdigit((unsigned char) c))
             {
                 val = (val << 4) +
                     (c + 10 - (islower((unsigned char) c) ? 'a' : 'A'));
                 cp++;
                 continue;
             }
             break;
         }
         if (*cp == '.')
         {
             /*
              * Internet format: a.b.c.d a.b.c   (with c treated as 16-bits)
              * a.b     (with b treated as 24 bits)
              */
             if (pp >= parts + 3 || val > 0xff)
                 return 0;
             *pp++ = val, cp++;
         }
         else
             break;
     }

     /*
      * Check for trailing junk.
      */
     while (*cp)
         if (!isspace((unsigned char) *cp++))
             return 0;

     /*
      * Concoct the address according to the number of parts specified.
      */
     n = pp - parts + 1;
     switch (n)
     {

         case 1:         /* a -- 32 bits */
             break;

         case 2:         /* a.b -- 8.24 bits */
             if (val > 0xffffff)
                 return 0;
             val |= parts[0] << 24;
             break;

         case 3:         /* a.b.c -- 8.8.16 bits */
             if (val > 0xffff)
                 return 0;
             val |= (parts[0] << 24) | (parts[1] << 16);
             break;

         case 4:         /* a.b.c.d -- 8.8.8.8 bits */
             if (val > 0xff)
                 return 0;
             val |= (parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8);
             break;
     }

     *addr = htonl(val);
     return 1;

}