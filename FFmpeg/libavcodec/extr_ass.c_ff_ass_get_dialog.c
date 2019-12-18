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
 char* av_asprintf (char*,int,int,char const*,char const*,char const*) ; 

char *ff_ass_get_dialog(int readorder, int layer, const char *style,
                        const char *speaker, const char *text)
{
    return av_asprintf("%d,%d,%s,%s,0,0,0,,%s",
                       readorder, layer, style ? style : "Default",
                       speaker ? speaker : "", text);
}