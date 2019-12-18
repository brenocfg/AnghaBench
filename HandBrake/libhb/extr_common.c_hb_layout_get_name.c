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
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_get_channel_layout_string (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hb_layout_get_name(char * name, int size, int64_t layout)
{
    av_get_channel_layout_string(name, size, 0, layout);
}