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
struct file {int dummy; } ;
typedef  int png_uint_32 ;

/* Variables and functions */
 int EOF ; 
 int read_byte (struct file*) ; 

__attribute__((used)) static unsigned int
read_4(struct file *file, png_uint_32 *pu)
   /* Read four bytes, returns the number of bytes read successfully and, if all
    * four bytes are read, assigns the result to *pu.
    */
{
   unsigned int i = 0;
   png_uint_32 val = 0;

   do
   {
      int ch = read_byte(file);

      if (ch == EOF)
         return i;

      val = (val << 8) + ch;
   } while (++i < 4);

   *pu = val;
   return i;
}