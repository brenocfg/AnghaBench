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
struct segment {int dummy; } ;
struct playlist {size_t cur_seq_no; size_t start_seq_no; struct segment** segments; } ;

/* Variables and functions */

__attribute__((used)) static struct segment *current_segment(struct playlist *pls)
{
    return pls->segments[pls->cur_seq_no - pls->start_seq_no];
}