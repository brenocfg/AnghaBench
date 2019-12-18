#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ start; scalar_t__ new_chap; } ;
struct TYPE_6__ {TYPE_1__ s; } ;
typedef  TYPE_2__ hb_buffer_t ;

/* Variables and functions */

__attribute__((used)) static inline void copy_chapter( hb_buffer_t * dst, hb_buffer_t * src )
{
    // Propagate any chapter breaks for the worker if and only if the
    // output frame has the same time stamp as the input frame (any
    // worker that delays frames has to propagate the chapter marks itself
    // and workers that move chapter marks to a different time should set
    // 'src' to NULL so that this code won't generate spurious duplicates.)
    if( src && dst && src->s.start == dst->s.start && src->s.new_chap != 0)
    {
        // restore log below to debug chapter mark propagation problems
        dst->s.new_chap = src->s.new_chap;
    }
}