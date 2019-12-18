#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  opaque; scalar_t__ (* customAlloc ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  customFree; } ;
typedef  TYPE_1__ ZSTDv07_customMem ;
struct TYPE_9__ {int /*<<< orphan*/  customMem; } ;
typedef  TYPE_2__ ZSTDv07_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTDv07_decompressBegin (TYPE_2__*) ; 
 TYPE_1__ defaultCustomMem ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int) ; 

ZSTDv07_DCtx* ZSTDv07_createDCtx_advanced(ZSTDv07_customMem customMem)
{
    ZSTDv07_DCtx* dctx;

    if (!customMem.customAlloc && !customMem.customFree)
        customMem = defaultCustomMem;

    if (!customMem.customAlloc || !customMem.customFree)
        return NULL;

    dctx = (ZSTDv07_DCtx*) customMem.customAlloc(customMem.opaque, sizeof(ZSTDv07_DCtx));
    if (!dctx) return NULL;
    memcpy(&dctx->customMem, &customMem, sizeof(ZSTDv07_customMem));
    ZSTDv07_decompressBegin(dctx);
    return dctx;
}