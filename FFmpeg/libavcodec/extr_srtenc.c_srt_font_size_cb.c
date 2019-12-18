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
 int /*<<< orphan*/  srt_print (void*,char*,int) ; 
 int /*<<< orphan*/  srt_stack_push_pop (void*,float,int) ; 

__attribute__((used)) static void srt_font_size_cb(void *priv, int size)
{
    srt_stack_push_pop(priv, 'f', size < 0);
    if (size >= 0)
        srt_print(priv, "<font size=\"%d\">", size);
}