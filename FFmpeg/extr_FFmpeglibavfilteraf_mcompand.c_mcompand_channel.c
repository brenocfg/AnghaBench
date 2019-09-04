#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {double* volume; scalar_t__ delay_buf_cnt; scalar_t__ delay_size; size_t delay_buf_ptr; TYPE_1__* delay_buf; int /*<<< orphan*/  transfer_fn; } ;
struct TYPE_8__ {size_t delay_buf_size; } ;
struct TYPE_7__ {scalar_t__* extended_data; } ;
typedef  TYPE_2__ MCompandContext ;
typedef  TYPE_3__ CompBand ;

/* Variables and functions */
 int /*<<< orphan*/  fabs (double) ; 
 double get_volume (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  update_volume (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mcompand_channel(MCompandContext *c, CompBand *l, double *ibuf, double *obuf, int len, int ch)
{
    int i;

    for (i = 0; i < len; i++) {
        double level_in_lin, level_out_lin, checkbuf;
        /* Maintain the volume fields by simulating a leaky pump circuit */
        update_volume(l, fabs(ibuf[i]), ch);

        /* Volume memory is updated: perform compand */
        level_in_lin = l->volume[ch];
        level_out_lin = get_volume(&l->transfer_fn, level_in_lin);

        if (c->delay_buf_size <= 0) {
            checkbuf = ibuf[i] * level_out_lin;
            obuf[i] = checkbuf;
        } else {
            double *delay_buf = (double *)l->delay_buf->extended_data[ch];

            /* FIXME: note that this lookahead algorithm is really lame:
               the response to a peak is released before the peak
               arrives. */

            /* because volume application delays differ band to band, but
               total delay doesn't, the volume is applied in an iteration
               preceding that in which the sample goes to obuf, except in
               the band(s) with the longest vol app delay.

               the offset between delay_buf_ptr and the sample to apply
               vol to, is a constant equal to the difference between this
               band's delay and the longest delay of all the bands. */

            if (l->delay_buf_cnt >= l->delay_size) {
                checkbuf =
                    delay_buf[(l->delay_buf_ptr +
                               c->delay_buf_size -
                               l->delay_size) % c->delay_buf_size] * level_out_lin;
                delay_buf[(l->delay_buf_ptr + c->delay_buf_size -
                           l->delay_size) % c->delay_buf_size] = checkbuf;
            }
            if (l->delay_buf_cnt >= c->delay_buf_size) {
                obuf[i] = delay_buf[l->delay_buf_ptr];
            } else {
                l->delay_buf_cnt++;
            }
            delay_buf[l->delay_buf_ptr++] = ibuf[i];
            l->delay_buf_ptr %= c->delay_buf_size;
        }
    }

    return 0;
}