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
typedef  int uint8_t ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (int /*<<< orphan*/ ) ; 
 char* av_get_known_color_name (int,int const**) ; 
 int /*<<< orphan*/  color_table ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void test_av_get_known_color_name(void)
{
    int i;
    const uint8_t *rgba;
    const char *color;

    for (i = 0; i < FF_ARRAY_ELEMS(color_table); ++i) {
        color = av_get_known_color_name(i, &rgba);
        if (color)
            printf("%s -> R(%d) G(%d) B(%d) A(%d)\n",
                    color, rgba[0], rgba[1], rgba[2], rgba[3]);
        else
            printf("Color ID: %d not found\n", i);
    }
}