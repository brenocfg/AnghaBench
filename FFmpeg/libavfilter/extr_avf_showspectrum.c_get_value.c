#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* priv; } ;
struct TYPE_4__ {float** magnitudes; float** phases; int data; int scale; } ;
typedef  TYPE_1__ ShowSpectrumContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
#define  CBRT 135 
#define  D_MAGNITUDE 134 
#define  D_PHASE 133 
#define  FIFTHRT 132 
#define  FOURTHRT 131 
#define  LINEAR 130 
#define  LOG 129 
#define  SQRT 128 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 float av_clipf (float,int,int) ; 
 float cbrtf (float) ; 
 float log10f (float) ; 
 float powf (float,double) ; 
 float sqrtf (float) ; 

__attribute__((used)) static float get_value(AVFilterContext *ctx, int ch, int y)
{
    ShowSpectrumContext *s = ctx->priv;
    float *magnitudes = s->magnitudes[ch];
    float *phases = s->phases[ch];
    float a;

    switch (s->data) {
    case D_MAGNITUDE:
        /* get magnitude */
        a = magnitudes[y];
        break;
    case D_PHASE:
        /* get phase */
        a = phases[y];
        break;
    default:
        av_assert0(0);
    }

    /* apply scale */
    switch (s->scale) {
    case LINEAR:
        a = av_clipf(a, 0, 1);
        break;
    case SQRT:
        a = av_clipf(sqrtf(a), 0, 1);
        break;
    case CBRT:
        a = av_clipf(cbrtf(a), 0, 1);
        break;
    case FOURTHRT:
        a = av_clipf(sqrtf(sqrtf(a)), 0, 1);
        break;
    case FIFTHRT:
        a = av_clipf(powf(a, 0.20), 0, 1);
        break;
    case LOG:
        a = 1.f + log10f(av_clipf(a, 1e-6, 1)) / 6.f; // zero = -120dBFS
        break;
    default:
        av_assert0(0);
    }

    return a;
}