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
 int /*<<< orphan*/  check_shuffle_bytes (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  check_uyvy_to_422p () ; 
 int /*<<< orphan*/  ff_sws_rgb2rgb_init () ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  shuffle_bytes_0321 ; 
 int /*<<< orphan*/  shuffle_bytes_1230 ; 
 int /*<<< orphan*/  shuffle_bytes_2103 ; 
 int /*<<< orphan*/  shuffle_bytes_3012 ; 
 int /*<<< orphan*/  shuffle_bytes_3210 ; 

void checkasm_check_sw_rgb(void)
{
    ff_sws_rgb2rgb_init();

    check_shuffle_bytes(shuffle_bytes_2103, "shuffle_bytes_2103");
    report("shuffle_bytes_2103");

    check_shuffle_bytes(shuffle_bytes_0321, "shuffle_bytes_0321");
    report("shuffle_bytes_0321");

    check_shuffle_bytes(shuffle_bytes_1230, "shuffle_bytes_1230");
    report("shuffle_bytes_1230");

    check_shuffle_bytes(shuffle_bytes_3012, "shuffle_bytes_3012");
    report("shuffle_bytes_3012");

    check_shuffle_bytes(shuffle_bytes_3210, "shuffle_bytes_3210");
    report("shuffle_bytes_3210");

    check_uyvy_to_422p();
    report("uyvytoyuv422");
}