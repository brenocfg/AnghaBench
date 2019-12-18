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
typedef  int png_uint_32 ;

/* Variables and functions */
 char png_icc_tag_char (int) ; 

__attribute__((used)) static void
png_icc_tag_name(char *name, png_uint_32 tag)
{
   name[0] = '\'';
   name[1] = png_icc_tag_char(tag >> 24);
   name[2] = png_icc_tag_char(tag >> 16);
   name[3] = png_icc_tag_char(tag >>  8);
   name[4] = png_icc_tag_char(tag      );
   name[5] = '\'';
}