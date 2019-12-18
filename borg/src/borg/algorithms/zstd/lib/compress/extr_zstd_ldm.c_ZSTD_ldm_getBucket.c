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
struct TYPE_5__ {int /*<<< orphan*/ * hashTable; } ;
typedef  TYPE_1__ ldmState_t ;
struct TYPE_6__ {size_t bucketSizeLog; } ;
typedef  TYPE_2__ ldmParams_t ;
typedef  int /*<<< orphan*/  ldmEntry_t ;

/* Variables and functions */

__attribute__((used)) static ldmEntry_t* ZSTD_ldm_getBucket(
        ldmState_t* ldmState, size_t hash, ldmParams_t const ldmParams)
{
    return ldmState->hashTable + (hash << ldmParams.bucketSizeLog);
}