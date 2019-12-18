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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_8__ {int outw; int outh; int inw; int inh; int plane; int xi; int yi; int c; int s; int const xprime; int const yprime; TYPE_4__* out; TYPE_4__* in; } ;
typedef  TYPE_2__ ThreadData ;
struct TYPE_11__ {TYPE_3__* priv; } ;
struct TYPE_10__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_7__ {int const* pixelstep; } ;
struct TYPE_9__ {TYPE_1__ draw; int /*<<< orphan*/ * (* interpolate_bilinear ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int const,int const) ;scalar_t__ use_bilinear; scalar_t__ angle; } ;
typedef  TYPE_3__ RotContext ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_RB24 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AV_RL16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AV_WB24 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_WL16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int const FIXP ; 
 scalar_t__ FLT_EPSILON ; 
 int M_PI ; 
 int av_clip (int,int /*<<< orphan*/ ,int const) ; 
 scalar_t__ fabs (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  simple_rotate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int const,int const) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int const,int const) ; 

__attribute__((used)) static int filter_slice(AVFilterContext *ctx, void *arg, int job, int nb_jobs)
{
    ThreadData *td = arg;
    AVFrame *in = td->in;
    AVFrame *out = td->out;
    RotContext *rot = ctx->priv;
    const int outw = td->outw, outh = td->outh;
    const int inw = td->inw, inh = td->inh;
    const int plane = td->plane;
    const int xi = td->xi, yi = td->yi;
    const int c = td->c, s = td->s;
    const int start = (outh *  job   ) / nb_jobs;
    const int end   = (outh * (job+1)) / nb_jobs;
    int xprime = td->xprime + start * s;
    int yprime = td->yprime + start * c;
    int i, j, x, y;

    for (j = start; j < end; j++) {
        x = xprime + xi + FIXP*(inw-1)/2;
        y = yprime + yi + FIXP*(inh-1)/2;

        if (fabs(rot->angle - 0) < FLT_EPSILON && outw == inw && outh == inh) {
            simple_rotate(out->data[plane] + j * out->linesize[plane],
                           in->data[plane] + j *  in->linesize[plane],
                          in->linesize[plane], 0, rot->draw.pixelstep[plane], outw);
        } else if (fabs(rot->angle - M_PI/2) < FLT_EPSILON && outw == inh && outh == inw) {
            simple_rotate(out->data[plane] + j * out->linesize[plane],
                           in->data[plane] + j * rot->draw.pixelstep[plane],
                          in->linesize[plane], 1, rot->draw.pixelstep[plane], outw);
        } else if (fabs(rot->angle - M_PI) < FLT_EPSILON && outw == inw && outh == inh) {
            simple_rotate(out->data[plane] + j * out->linesize[plane],
                           in->data[plane] + (outh-j-1) *  in->linesize[plane],
                          in->linesize[plane], 2, rot->draw.pixelstep[plane], outw);
        } else if (fabs(rot->angle - 3*M_PI/2) < FLT_EPSILON && outw == inh && outh == inw) {
            simple_rotate(out->data[plane] + j * out->linesize[plane],
                           in->data[plane] + (outh-j-1) * rot->draw.pixelstep[plane],
                          in->linesize[plane], 3, rot->draw.pixelstep[plane], outw);
        } else {

        for (i = 0; i < outw; i++) {
            int32_t v;
            int x1, y1;
            uint8_t *pin, *pout;
            x1 = x>>16;
            y1 = y>>16;

            /* the out-of-range values avoid border artifacts */
            if (x1 >= -1 && x1 <= inw && y1 >= -1 && y1 <= inh) {
                uint8_t inp_inv[4]; /* interpolated input value */
                pout = out->data[plane] + j * out->linesize[plane] + i * rot->draw.pixelstep[plane];
                if (rot->use_bilinear) {
                    pin = rot->interpolate_bilinear(inp_inv,
                                                    in->data[plane], in->linesize[plane], rot->draw.pixelstep[plane],
                                                    x, y, inw-1, inh-1);
                } else {
                    int x2 = av_clip(x1, 0, inw-1);
                    int y2 = av_clip(y1, 0, inh-1);
                    pin = in->data[plane] + y2 * in->linesize[plane] + x2 * rot->draw.pixelstep[plane];
                }
                switch (rot->draw.pixelstep[plane]) {
                case 1:
                    *pout = *pin;
                    break;
                case 2:
                    v = AV_RL16(pin);
                    AV_WL16(pout, v);
                    break;
                case 3:
                    v = AV_RB24(pin);
                    AV_WB24(pout, v);
                    break;
                case 4:
                    *((uint32_t *)pout) = *((uint32_t *)pin);
                    break;
                default:
                    memcpy(pout, pin, rot->draw.pixelstep[plane]);
                    break;
                }
            }
            x += c;
            y -= s;
        }
        }
        xprime += s;
        yprime += c;
    }

    return 0;
}