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
struct playlist {scalar_t__ n_segments; int /*<<< orphan*/  segments; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_segment_dynarray (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void free_segment_list(struct playlist *pls)
{
    free_segment_dynarray(pls->segments, pls->n_segments);
    av_freep(&pls->segments);
    pls->n_segments = 0;
}