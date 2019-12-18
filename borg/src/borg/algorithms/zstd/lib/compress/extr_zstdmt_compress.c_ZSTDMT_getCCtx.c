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
typedef  int /*<<< orphan*/  ZSTD_CCtx ;
struct TYPE_3__ {int availCCtx; int /*<<< orphan*/  cMem; int /*<<< orphan*/  poolMutex; int /*<<< orphan*/ ** cctx; } ;
typedef  TYPE_1__ ZSTDMT_CCtxPool ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*) ; 
 int /*<<< orphan*/ * ZSTD_createCCtx_advanced (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ZSTD_CCtx* ZSTDMT_getCCtx(ZSTDMT_CCtxPool* cctxPool)
{
    DEBUGLOG(5, "ZSTDMT_getCCtx");
    ZSTD_pthread_mutex_lock(&cctxPool->poolMutex);
    if (cctxPool->availCCtx) {
        cctxPool->availCCtx--;
        {   ZSTD_CCtx* const cctx = cctxPool->cctx[cctxPool->availCCtx];
            ZSTD_pthread_mutex_unlock(&cctxPool->poolMutex);
            return cctx;
    }   }
    ZSTD_pthread_mutex_unlock(&cctxPool->poolMutex);
    DEBUGLOG(5, "create one more CCtx");
    return ZSTD_createCCtx_advanced(cctxPool->cMem);   /* note : can be NULL, when creation fails ! */
}