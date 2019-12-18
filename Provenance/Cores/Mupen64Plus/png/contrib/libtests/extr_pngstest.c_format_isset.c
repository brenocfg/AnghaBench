#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int png_uint_32 ;
struct TYPE_3__ {int* bits; } ;
typedef  TYPE_1__ format_list ;

/* Variables and functions */
 int FORMAT_COUNT ; 

__attribute__((used)) static int format_isset(format_list *pf, png_uint_32 format)
{
   return format < FORMAT_COUNT &&
      (pf->bits[format >> 5] & (((png_uint_32)1) << (format & 31))) != 0;
}