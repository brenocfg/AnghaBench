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
typedef  int /*<<< orphan*/  ZSTDMT_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/ * ZSTDMT_createCCtx_advanced (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_defaultCMem ; 

ZSTDMT_CCtx* ZSTDMT_createCCtx(unsigned nbWorkers)
{
    return ZSTDMT_createCCtx_advanced(nbWorkers, ZSTD_defaultCMem);
}