#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t minMatchLength; scalar_t__ enableLdm; } ;
typedef  TYPE_1__ ldmParams_t ;

/* Variables and functions */

size_t ZSTD_ldm_getMaxNbSeq(ldmParams_t params, size_t maxChunkSize)
{
    return params.enableLdm ? (maxChunkSize / params.minMatchLength) : 0;
}