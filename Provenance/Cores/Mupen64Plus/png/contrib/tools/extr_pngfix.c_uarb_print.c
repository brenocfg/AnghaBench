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
typedef  int /*<<< orphan*/  udigit ;
typedef  unsigned long* uarb ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,unsigned long) ; 
 int /*<<< orphan*/  uarb_printx (unsigned long*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
uarb_print(uarb num, int digits, FILE *out)
   /* Prints 'num' as a decimal if it will fit in an unsigned long, else as a
    * hexadecimal number.  Notice that the results vary for images over 4GByte
    * in a system dependent way, and the hexadecimal form doesn't work very well
    * in awk script input.
    *
    *
    * TODO: write uarb_div10
    */
{
   if (digits * sizeof (udigit) > sizeof (unsigned long))
      uarb_printx(num, digits, out);

   else
   {
      unsigned long n = 0;

      while (digits > 0)
         n = (n << 16) + num[--digits];

      fprintf(out, "%lu", n);
   }
}