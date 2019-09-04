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
typedef  int int64_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AV_TIME_BASE ; 
 int /*<<< orphan*/  avio_printf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void write_time(AVIOContext *out, int64_t time)
{
    int seconds = time / AV_TIME_BASE;
    int fractions = time % AV_TIME_BASE;
    int minutes = seconds / 60;
    int hours = minutes / 60;
    seconds %= 60;
    minutes %= 60;
    avio_printf(out, "PT");
    if (hours)
        avio_printf(out, "%dH", hours);
    if (hours || minutes)
        avio_printf(out, "%dM", minutes);
    avio_printf(out, "%d.%dS", seconds, fractions / (AV_TIME_BASE / 10));
}