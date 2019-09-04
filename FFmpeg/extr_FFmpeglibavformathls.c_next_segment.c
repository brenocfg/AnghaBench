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
struct playlist {int cur_seq_no; int start_seq_no; int n_segments; struct segment** segments; } ;

/* Variables and functions */

__attribute__((used)) static struct segment *next_segment(struct playlist *pls)
{
    int n = pls->cur_seq_no - pls->start_seq_no + 1;
    if (n >= pls->n_segments)
        return NULL;
    return pls->segments[n];
}