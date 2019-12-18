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
 scalar_t__ g_FrameBuffer ; 
 scalar_t__ g_VertexBuffer ; 
 int g_buf_height ; 
 int g_buf_width ; 

int Java_org_yabause_android_YabauseRunnable_cleanup()
{
    g_FrameBuffer = 0;
    g_VertexBuffer = 0;
    g_buf_width = -1;
    g_buf_height = -1;
}