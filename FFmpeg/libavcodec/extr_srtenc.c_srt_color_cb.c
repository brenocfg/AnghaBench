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
 int /*<<< orphan*/  srt_print (void*,char*,unsigned int) ; 
 int /*<<< orphan*/  srt_stack_push_pop (void*,float,int) ; 

__attribute__((used)) static void srt_color_cb(void *priv, unsigned int color, unsigned int color_id)
{
    if (color_id > 1)
        return;
    srt_stack_push_pop(priv, 'f', color == 0xFFFFFFFF);
    if (color != 0xFFFFFFFF)
        srt_print(priv, "<font color=\"#%06x\">",
              (color & 0xFF0000) >> 16 | color & 0xFF00 | (color & 0xFF) << 16);
}