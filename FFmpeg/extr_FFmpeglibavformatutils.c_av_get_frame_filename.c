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
 int av_get_frame_filename2 (char*,int,char const*,int,int /*<<< orphan*/ ) ; 

int av_get_frame_filename(char *buf, int buf_size, const char *path, int number)
{
    return av_get_frame_filename2(buf, buf_size, path, number, 0);
}