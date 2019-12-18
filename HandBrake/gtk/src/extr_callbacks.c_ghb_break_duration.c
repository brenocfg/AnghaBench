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
typedef  int gint64 ;
typedef  int gint ;

/* Variables and functions */

void ghb_break_duration(gint64 duration, gint *hh, gint *mm, gint *ss)
{
    *hh = duration / (60*60);
    *mm = (duration / 60) % 60;
    *ss = duration % 60;
}