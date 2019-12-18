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
 int /*<<< orphan*/  webvtt_print (void*,char*,char) ; 
 int /*<<< orphan*/  webvtt_stack_push_pop (void*,char,int) ; 

__attribute__((used)) static void webvtt_style_cb(void *priv, char style, int close)
{
    if (style == 's') // strikethrough unsupported
        return;

    webvtt_stack_push_pop(priv, style, close);
    if (!close)
        webvtt_print(priv, "<%c>", style);
}