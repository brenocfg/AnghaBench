#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t footprint_limit; } ;

/* Variables and functions */
 size_t MAX_SIZE_T ; 
 TYPE_1__* gm ; 
 size_t granularity_align (size_t) ; 

size_t dlmalloc_set_footprint_limit(size_t bytes) {
    size_t result;  /* invert sense of 0 */
    if (bytes == 0)
        result = granularity_align(1); /* Use minimal size */
    if (bytes == MAX_SIZE_T)
        result = 0;                    /* disable */
    else
        result = granularity_align(bytes);
    return gm->footprint_limit = result;
}