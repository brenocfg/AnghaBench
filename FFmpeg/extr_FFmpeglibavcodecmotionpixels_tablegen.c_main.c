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
 int /*<<< orphan*/  motionpixels_tableinit () ; 
 int /*<<< orphan*/  mp_rgb_yuv_table ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  write_fileheader () ; 
 int /*<<< orphan*/  write_int8_t_2d_array (int /*<<< orphan*/ ,int,int) ; 

int main(void)
{
    motionpixels_tableinit();

    write_fileheader();

    printf("static const YuvPixel mp_rgb_yuv_table[1 << 15] = {\n");
    write_int8_t_2d_array(mp_rgb_yuv_table, 1 << 15, 3);
    printf("};\n");

    return 0;
}