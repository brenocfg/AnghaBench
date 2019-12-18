#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ num_files; scalar_t__ csize; scalar_t__ size; } ;
struct TYPE_7__ {scalar_t__ num_files; scalar_t__ csize; scalar_t__ size; } ;
struct TYPE_9__ {TYPE_2__ totals; TYPE_1__ parts; int /*<<< orphan*/ * chunks; } ;
struct TYPE_11__ {TYPE_3__ user; } ;
struct TYPE_10__ {scalar_t__ size; scalar_t__ tail; scalar_t__ head; int /*<<< orphan*/ * buf; TYPE_5__ ctx; } ;
typedef  int /*<<< orphan*/  HashIndex ;
typedef  TYPE_4__ CacheSyncCtx ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  unpack_init (TYPE_5__*) ; 

__attribute__((used)) static CacheSyncCtx *
cache_sync_init(HashIndex *chunks)
{
    CacheSyncCtx *ctx;
    if (!(ctx = (CacheSyncCtx*)malloc(sizeof(CacheSyncCtx)))) {
        return NULL;
    }

    unpack_init(&ctx->ctx);
    /* needs to be set only once */
    ctx->ctx.user.chunks = chunks;
    ctx->ctx.user.parts.size = 0;
    ctx->ctx.user.parts.csize = 0;
    ctx->ctx.user.parts.num_files = 0;
    ctx->ctx.user.totals.size = 0;
    ctx->ctx.user.totals.csize = 0;
    ctx->ctx.user.totals.num_files = 0;
    ctx->buf = NULL;
    ctx->head = 0;
    ctx->tail = 0;
    ctx->size = 0;

    return ctx;
}