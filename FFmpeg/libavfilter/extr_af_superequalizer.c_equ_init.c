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
struct TYPE_4__ {int aa; int winlen; int tabsize; int* fact; int /*<<< orphan*/  iza; void* fsamples; void* irest; void* ires; void* irdft; void* rdft; } ;
typedef  TYPE_1__ SuperEqualizerContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DFT_R2C ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  IDFT_C2R ; 
 int M ; 
 int /*<<< orphan*/  alpha (int) ; 
 void* av_calloc (int,int) ; 
 void* av_rdft_init (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  izero (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int equ_init(SuperEqualizerContext *s, int wb)
{
    int i,j;

    s->rdft  = av_rdft_init(wb, DFT_R2C);
    s->irdft = av_rdft_init(wb, IDFT_C2R);
    if (!s->rdft || !s->irdft)
        return AVERROR(ENOMEM);

    s->aa = 96;
    s->winlen = (1 << (wb-1))-1;
    s->tabsize  = 1 << wb;

    s->ires     = av_calloc(s->tabsize, sizeof(float));
    s->irest    = av_calloc(s->tabsize, sizeof(float));
    s->fsamples = av_calloc(s->tabsize, sizeof(float));

    for (i = 0; i <= M; i++) {
        s->fact[i] = 1;
        for (j = 1; j <= i; j++)
            s->fact[i] *= j;
    }

    s->iza = izero(s, alpha(s->aa));

    return 0;
}