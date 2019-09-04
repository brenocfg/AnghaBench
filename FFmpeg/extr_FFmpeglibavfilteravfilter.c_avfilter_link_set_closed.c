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
typedef  int /*<<< orphan*/  AVFilterLink ;

/* Variables and functions */
 int /*<<< orphan*/  AVERROR_EOF ; 
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ff_avfilter_link_set_out_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void avfilter_link_set_closed(AVFilterLink *link, int closed)
{
    ff_avfilter_link_set_out_status(link, closed ? AVERROR_EOF : 0, AV_NOPTS_VALUE);
}