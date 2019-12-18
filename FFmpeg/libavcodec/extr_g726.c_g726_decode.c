#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* int16_t ;
struct TYPE_10__ {int sign; } ;
struct TYPE_8__ {int* F; int* W; } ;
struct TYPE_9__ {int code_size; int yl; int td; int se; int sez; int* a; int* b; int* pk; int dms; int dml; int ap; int y; int yu; TYPE_3__* sr; TYPE_3__* dq; TYPE_1__ tbls; } ;
typedef  TYPE_2__ G726Context ;
typedef  TYPE_3__ Float11 ;

/* Variables and functions */
 int abs (int) ; 
 void* av_clip (int,int,int) ; 
 int av_clip_intp2 (int,int) ; 
 int /*<<< orphan*/  i2f (int,TYPE_3__*) ; 
 int inverse_quant (TYPE_2__*,int) ; 
 int mult (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int sgn (int) ; 

__attribute__((used)) static int16_t g726_decode(G726Context* c, int I)
{
    int dq, re_signal, pk0, fa1, i, tr, ylint, ylfrac, thr2, al, dq0;
    Float11 f;
    int I_sig= I >> (c->code_size - 1);

    dq = inverse_quant(c, I);

    /* Transition detect */
    ylint = (c->yl >> 15);
    ylfrac = (c->yl >> 10) & 0x1f;
    thr2 = (ylint > 9) ? 0x1f << 10 : (0x20 + ylfrac) << ylint;
    tr= (c->td == 1 && dq > ((3*thr2)>>2));

    if (I_sig)  /* get the sign */
        dq = -dq;
    re_signal = (int16_t)(c->se + dq);

    /* Update second order predictor coefficient A2 and A1 */
    pk0 = (c->sez + dq) ? sgn(c->sez + dq) : 0;
    dq0 = dq ? sgn(dq) : 0;
    if (tr) {
        c->a[0] = 0;
        c->a[1] = 0;
        for (i=0; i<6; i++)
            c->b[i] = 0;
    } else {
        /* This is a bit crazy, but it really is +255 not +256 */
        fa1 = av_clip_intp2((-c->a[0]*c->pk[0]*pk0)>>5, 8);

        c->a[1] += 128*pk0*c->pk[1] + fa1 - (c->a[1]>>7);
        c->a[1] = av_clip(c->a[1], -12288, 12288);
        c->a[0] += 64*3*pk0*c->pk[0] - (c->a[0] >> 8);
        c->a[0] = av_clip(c->a[0], -(15360 - c->a[1]), 15360 - c->a[1]);

        for (i=0; i<6; i++)
            c->b[i] += 128*dq0*sgn(-c->dq[i].sign) - (c->b[i]>>8);
    }

    /* Update Dq and Sr and Pk */
    c->pk[1] = c->pk[0];
    c->pk[0] = pk0 ? pk0 : 1;
    c->sr[1] = c->sr[0];
    i2f(re_signal, &c->sr[0]);
    for (i=5; i>0; i--)
        c->dq[i] = c->dq[i-1];
    i2f(dq, &c->dq[0]);
    c->dq[0].sign = I_sig; /* Isn't it crazy ?!?! */

    c->td = c->a[1] < -11776;

    /* Update Ap */
    c->dms += (c->tbls.F[I]<<4) + ((- c->dms) >> 5);
    c->dml += (c->tbls.F[I]<<4) + ((- c->dml) >> 7);
    if (tr)
        c->ap = 256;
    else {
        c->ap += (-c->ap) >> 4;
        if (c->y <= 1535 || c->td || abs((c->dms << 2) - c->dml) >= (c->dml >> 3))
            c->ap += 0x20;
    }

    /* Update Yu and Yl */
    c->yu = av_clip(c->y + c->tbls.W[I] + ((-c->y)>>5), 544, 5120);
    c->yl += c->yu + ((-c->yl)>>6);

    /* Next iteration for Y */
    al = (c->ap >= 256) ? 1<<6 : c->ap >> 2;
    c->y = (c->yl + (c->yu - (c->yl>>6))*al) >> 6;

    /* Next iteration for SE and SEZ */
    c->se = 0;
    for (i=0; i<6; i++)
        c->se += mult(i2f(c->b[i] >> 2, &f), &c->dq[i]);
    c->sez = c->se >> 1;
    for (i=0; i<2; i++)
        c->se += mult(i2f(c->a[i] >> 2, &f), &c->sr[i]);
    c->se >>= 1;

    return av_clip(re_signal * 4, -0xffff, 0xffff);
}