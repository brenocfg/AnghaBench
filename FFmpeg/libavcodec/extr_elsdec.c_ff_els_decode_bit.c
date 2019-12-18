#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct TYPE_6__ {size_t ALps; size_t next0; size_t next1; scalar_t__ AMps; } ;
struct TYPE_5__ {size_t j; int t; int diff; int x; scalar_t__ err; } ;
typedef  TYPE_1__ ElsDecCtx ;

/* Variables and functions */
 int ELS_JOTS_PER_BYTE ; 
 int FFMIN (int,int) ; 
 TYPE_4__* Ladder ; 
 int* els_exp_tab ; 
 int els_import_byte (TYPE_1__*) ; 

int ff_els_decode_bit(ElsDecCtx *ctx, uint8_t *rung)
{
    int z, bit, ret;
    const uint32_t *pAllowable = &els_exp_tab[ELS_JOTS_PER_BYTE * 3];

    if (ctx->err)
        return 0;

    z          = pAllowable[ctx->j + Ladder[*rung].ALps];
    ctx->t    -= z;
    ctx->diff -= z;
    if (ctx->diff > 0)
        return *rung & 1;   /* shortcut for x < t > pAllowable[j - 1] */

    if (ctx->t > ctx->x) {  /* decode most probable symbol (MPS) */
        ctx->j += Ladder[*rung].AMps;
        while (ctx->t > pAllowable[ctx->j])
            ctx->j++;

        if (ctx->j <= 0) { /* MPS: import one byte from bytestream. */
            ret = els_import_byte(ctx);
            if (ret < 0)
                return ret;
        }

        z     = ctx->t;
        bit   = *rung & 1;
        *rung = Ladder[*rung].next0;
    } else { /* decode less probable symbol (LPS) */
        ctx->x -= ctx->t;
        ctx->t  = z;

        ctx->j += Ladder[*rung].ALps;
        if (ctx->j <= 0) {
            /* LPS: import one byte from bytestream. */
            z <<= 8;
            ret = els_import_byte(ctx);
            if (ret < 0)
                return ret;
            if (ctx->j <= 0) {
                /* LPS: import second byte from bytestream. */
                z <<= 8;
                ret = els_import_byte(ctx);
                if (ret < 0)
                    return ret;
                while (pAllowable[ctx->j - 1] >= z)
                    ctx->j--;
            }
        }

        bit   = !(*rung & 1);
        *rung = Ladder[*rung].next1;
    }

    ctx->diff = FFMIN(z - ctx->x, z - pAllowable[ctx->j - 1]);

    return bit;
}