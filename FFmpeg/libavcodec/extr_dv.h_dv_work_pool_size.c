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
struct TYPE_5__ {int n_difchan; int difseg_size; } ;
typedef  TYPE_1__ AVDVProfile ;

/* Variables and functions */
 scalar_t__ DV_PROFILE_IS_1080i50 (TYPE_1__ const*) ; 
 scalar_t__ DV_PROFILE_IS_720p50 (TYPE_1__ const*) ; 

__attribute__((used)) static inline int dv_work_pool_size(const AVDVProfile *d)
{
    int size = d->n_difchan * d->difseg_size * 27;
    if (DV_PROFILE_IS_1080i50(d))
        size -= 3 * 27;
    if (DV_PROFILE_IS_720p50(d))
        size -= 4 * 27;
    return size;
}