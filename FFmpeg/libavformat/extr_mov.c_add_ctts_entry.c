#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_5__ {int count; int duration; } ;
typedef  TYPE_1__ MOVStts ;

/* Variables and functions */
 size_t const FFMAX (size_t const,int) ; 
 int UINT_MAX ; 
 TYPE_1__* av_fast_realloc (TYPE_1__*,unsigned int*,size_t const) ; 

__attribute__((used)) static int64_t add_ctts_entry(MOVStts** ctts_data, unsigned int* ctts_count, unsigned int* allocated_size,
                              int count, int duration)
{
    MOVStts *ctts_buf_new;
    const size_t min_size_needed = (*ctts_count + 1) * sizeof(MOVStts);
    const size_t requested_size =
        min_size_needed > *allocated_size ?
        FFMAX(min_size_needed, 2 * (*allocated_size)) :
        min_size_needed;

    if((unsigned)(*ctts_count) >= UINT_MAX / sizeof(MOVStts) - 1)
        return -1;

    ctts_buf_new = av_fast_realloc(*ctts_data, allocated_size, requested_size);

    if(!ctts_buf_new)
        return -1;

    *ctts_data = ctts_buf_new;

    ctts_buf_new[*ctts_count].count = count;
    ctts_buf_new[*ctts_count].duration = duration;

    *ctts_count = (*ctts_count) + 1;
    return *ctts_count;
}