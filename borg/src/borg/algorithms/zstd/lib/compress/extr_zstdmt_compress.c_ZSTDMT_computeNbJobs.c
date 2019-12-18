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
typedef  int /*<<< orphan*/  ZSTD_CCtx_params ;

/* Variables and functions */
 unsigned int MIN (unsigned int const,unsigned int) ; 
 size_t ZSTDMT_computeTargetJobLog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static unsigned
ZSTDMT_computeNbJobs(ZSTD_CCtx_params params, size_t srcSize, unsigned nbWorkers)
{
    assert(nbWorkers>0);
    {   size_t const jobSizeTarget = (size_t)1 << ZSTDMT_computeTargetJobLog(params);
        size_t const jobMaxSize = jobSizeTarget << 2;
        size_t const passSizeMax = jobMaxSize * nbWorkers;
        unsigned const multiplier = (unsigned)(srcSize / passSizeMax) + 1;
        unsigned const nbJobsLarge = multiplier * nbWorkers;
        unsigned const nbJobsMax = (unsigned)(srcSize / jobSizeTarget) + 1;
        unsigned const nbJobsSmall = MIN(nbJobsMax, nbWorkers);
        return (multiplier>1) ? nbJobsLarge : nbJobsSmall;
}   }