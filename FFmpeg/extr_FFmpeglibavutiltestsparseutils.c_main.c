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
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  test_av_find_info_tag () ; 
 int /*<<< orphan*/  test_av_get_known_color_name () ; 
 int /*<<< orphan*/  test_av_parse_color () ; 
 int /*<<< orphan*/  test_av_parse_time () ; 
 int /*<<< orphan*/  test_av_parse_video_rate () ; 
 int /*<<< orphan*/  test_av_small_strptime () ; 

int main(void)
{
    printf("Testing av_parse_video_rate()\n");
    test_av_parse_video_rate();

    printf("\nTesting av_parse_color()\n");
    test_av_parse_color();

    printf("\nTesting av_small_strptime()\n");
    test_av_small_strptime();

    printf("\nTesting av_parse_time()\n");
    test_av_parse_time();

    printf("\nTesting av_get_known_color_name()\n");
    test_av_get_known_color_name();

    printf("\nTesting av_find_info_tag()\n");
    test_av_find_info_tag();
    return 0;
}