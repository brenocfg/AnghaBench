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
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int url_open_dyn_buf_internal (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

int avio_open_dyn_buf(AVIOContext **s)
{
    return url_open_dyn_buf_internal(s, 0);
}