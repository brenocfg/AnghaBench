#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ capacity; scalar_t__ start; } ;
typedef  TYPE_4__ buffer_t ;
typedef  int /*<<< orphan*/  ZSTD_pthread_mutex_t ;
struct TYPE_11__ {int /*<<< orphan*/  ldmWindowCond; int /*<<< orphan*/  ldmWindow; int /*<<< orphan*/  ldmWindowMutex; } ;
struct TYPE_9__ {scalar_t__ enableLdm; } ;
struct TYPE_10__ {TYPE_1__ ldmParams; } ;
struct TYPE_13__ {TYPE_3__ serial; TYPE_2__ params; } ;
typedef  TYPE_5__ ZSTDMT_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,...) ; 
 scalar_t__ ZSTDMT_doesOverlapWindow (TYPE_4__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_PTHREAD_MUTEX_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ZSTDMT_waitForLdmComplete(ZSTDMT_CCtx* mtctx, buffer_t buffer)
{
    if (mtctx->params.ldmParams.enableLdm) {
        ZSTD_pthread_mutex_t* mutex = &mtctx->serial.ldmWindowMutex;
        DEBUGLOG(5, "ZSTDMT_waitForLdmComplete");
        DEBUGLOG(5, "source  [0x%zx, 0x%zx)",
                    (size_t)buffer.start,
                    (size_t)buffer.start + buffer.capacity);
        ZSTD_PTHREAD_MUTEX_LOCK(mutex);
        while (ZSTDMT_doesOverlapWindow(buffer, mtctx->serial.ldmWindow)) {
            DEBUGLOG(5, "Waiting for LDM to finish...");
            ZSTD_pthread_cond_wait(&mtctx->serial.ldmWindowCond, mutex);
        }
        DEBUGLOG(6, "Done waiting for LDM to finish");
        ZSTD_pthread_mutex_unlock(mutex);
    }
}