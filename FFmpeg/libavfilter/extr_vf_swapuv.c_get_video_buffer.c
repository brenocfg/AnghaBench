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
typedef  int /*<<< orphan*/  AVFrame ;
typedef  int /*<<< orphan*/  AVFilterLink ;

/* Variables and functions */
 int /*<<< orphan*/  do_swap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_default_get_video_buffer (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static AVFrame *get_video_buffer(AVFilterLink *link, int w, int h)
{
    AVFrame *picref = ff_default_get_video_buffer(link, w, h);
    do_swap(picref);
    return picref;
}