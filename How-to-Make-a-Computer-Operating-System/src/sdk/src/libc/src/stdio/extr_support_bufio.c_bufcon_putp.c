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
 int /*<<< orphan*/  bufcon_putc (char*,unsigned char) ; 

char*  bufcon_putp( char *buffer, unsigned int p )
{
   int offset;
   unsigned char c;
   int found = 0;

   for ( offset = 28; offset >= 0; offset -= 4 )
   {
     c = (p>>offset) & 0xF;
     if ( c != 0 ) found = 1;
     if ( found == 1 )
     {
     	if ( c < 10 ) bufcon_putc( buffer, c + '0' );
     	         else bufcon_putc( buffer, c - 10 + 'a' );
     }
   }
   
   if (found == 0 ) bufcon_putc( buffer, '0' );
   
   return buffer;
}