#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  const* ddict; } ;
typedef  TYPE_1__ ZSTD_DStream ;
typedef  int /*<<< orphan*/  ZSTD_DDict ;

/* Variables and functions */
 size_t ZSTD_initDStream (TYPE_1__*) ; 

size_t ZSTD_initDStream_usingDDict(ZSTD_DStream* dctx, const ZSTD_DDict* ddict)
{
    size_t const initResult = ZSTD_initDStream(dctx);
    dctx->ddict = ddict;
    return initResult;
}