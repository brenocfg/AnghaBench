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
typedef  int int32_t ;
struct TYPE_5__ {int* lastA; int* buf; int** coeffsA; int* historybuffer; int* filterA; } ;
struct TYPE_6__ {int** decoded; TYPE_1__ predictor; } ;
typedef  TYPE_1__ APEPredictor ;
typedef  TYPE_2__ APEContext ;

/* Variables and functions */
 void* APESIGN (int) ; 
 int HISTORY_SIZE ; 
 int PREDICTOR_SIZE ; 
 size_t YADAPTCOEFFSA ; 
 size_t YDELAYA ; 
 int /*<<< orphan*/  ape_apply_filters (TYPE_2__*,int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 

__attribute__((used)) static void predictor_decode_mono_3950(APEContext *ctx, int count)
{
    APEPredictor *p = &ctx->predictor;
    int32_t *decoded0 = ctx->decoded[0];
    int32_t predictionA, currentA, A, sign;

    ape_apply_filters(ctx, ctx->decoded[0], NULL, count);

    currentA = p->lastA[0];

    while (count--) {
        A = *decoded0;

        p->buf[YDELAYA] = currentA;
        p->buf[YDELAYA - 1] = p->buf[YDELAYA] - p->buf[YDELAYA - 1];

        predictionA = p->buf[YDELAYA    ] * p->coeffsA[0][0] +
                      p->buf[YDELAYA - 1] * p->coeffsA[0][1] +
                      p->buf[YDELAYA - 2] * p->coeffsA[0][2] +
                      p->buf[YDELAYA - 3] * p->coeffsA[0][3];

        currentA = A + (predictionA >> 10);

        p->buf[YADAPTCOEFFSA]     = APESIGN(p->buf[YDELAYA    ]);
        p->buf[YADAPTCOEFFSA - 1] = APESIGN(p->buf[YDELAYA - 1]);

        sign = APESIGN(A);
        p->coeffsA[0][0] += p->buf[YADAPTCOEFFSA    ] * sign;
        p->coeffsA[0][1] += p->buf[YADAPTCOEFFSA - 1] * sign;
        p->coeffsA[0][2] += p->buf[YADAPTCOEFFSA - 2] * sign;
        p->coeffsA[0][3] += p->buf[YADAPTCOEFFSA - 3] * sign;

        p->buf++;

        /* Have we filled the history buffer? */
        if (p->buf == p->historybuffer + HISTORY_SIZE) {
            memmove(p->historybuffer, p->buf,
                    PREDICTOR_SIZE * sizeof(*p->historybuffer));
            p->buf = p->historybuffer;
        }

        p->filterA[0] = currentA + ((int)(p->filterA[0] * 31U) >> 5);
        *(decoded0++) = p->filterA[0];
    }

    p->lastA[0] = currentA;
}