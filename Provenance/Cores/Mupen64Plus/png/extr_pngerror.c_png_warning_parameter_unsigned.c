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
typedef  int /*<<< orphan*/  png_alloc_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_FORMAT_NUMBER (char*,int,int /*<<< orphan*/ ) ; 
 int PNG_NUMBER_BUFFER_SIZE ; 
 int /*<<< orphan*/  png_warning_parameter (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
png_warning_parameter_unsigned(png_warning_parameters p, int number, int format,
    png_alloc_size_t value)
{
   char buffer[PNG_NUMBER_BUFFER_SIZE];
   png_warning_parameter(p, number, PNG_FORMAT_NUMBER(buffer, format, value));
}