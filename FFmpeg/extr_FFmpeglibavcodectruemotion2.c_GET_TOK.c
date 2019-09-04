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
struct TYPE_3__ {size_t* tok_ptrs; size_t* tok_lens; int error; size_t** tokens; int** deltas; int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ TM2Context ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 size_t TM2_DELTAS ; 
 int TM2_MOT ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,...) ; 

__attribute__((used)) static inline int GET_TOK(TM2Context *ctx,int type)
{
    if (ctx->tok_ptrs[type] >= ctx->tok_lens[type]) {
        av_log(ctx->avctx, AV_LOG_ERROR, "Read token from stream %i out of bounds (%i>=%i)\n", type, ctx->tok_ptrs[type], ctx->tok_lens[type]);
        ctx->error = 1;
        return 0;
    }
    if (type <= TM2_MOT) {
        if (ctx->tokens[type][ctx->tok_ptrs[type]] >= TM2_DELTAS) {
            av_log(ctx->avctx, AV_LOG_ERROR, "token %d is too large\n", ctx->tokens[type][ctx->tok_ptrs[type]]);
            return 0;
        }
        return ctx->deltas[type][ctx->tokens[type][ctx->tok_ptrs[type]++]];
    }
    return ctx->tokens[type][ctx->tok_ptrs[type]++];
}