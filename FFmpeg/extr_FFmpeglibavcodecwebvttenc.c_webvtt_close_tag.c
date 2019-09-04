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
typedef  int /*<<< orphan*/  WebVTTContext ;

/* Variables and functions */
 int /*<<< orphan*/  webvtt_print (int /*<<< orphan*/ *,char*,char) ; 

__attribute__((used)) static void webvtt_close_tag(WebVTTContext *s, char tag)
{
    webvtt_print(s, "</%c>", tag);
}