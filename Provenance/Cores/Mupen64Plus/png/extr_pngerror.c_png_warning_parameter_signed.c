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
typedef  int /*<<< orphan*/  png_warning_parameters ;
typedef  scalar_t__ png_int_32 ;
typedef  char* png_charp ;
typedef  int png_alloc_size_t ;

/* Variables and functions */
 char* PNG_FORMAT_NUMBER (char*,int,int) ; 
 int PNG_NUMBER_BUFFER_SIZE ; 
 int /*<<< orphan*/  png_warning_parameter (int /*<<< orphan*/ ,int,char*) ; 

void
png_warning_parameter_signed(png_warning_parameters p, int number, int format,
    png_int_32 value)
{
   png_alloc_size_t u;
   png_charp str;
   char buffer[PNG_NUMBER_BUFFER_SIZE];

   /* Avoid overflow by doing the negate in a png_alloc_size_t: */
   u = (png_alloc_size_t)value;
   if (value < 0)
      u = ~u + 1;

   str = PNG_FORMAT_NUMBER(buffer, format, u);

   if (value < 0 && str > buffer)
      *--str = '-';

   png_warning_parameter(p, number, str);
}