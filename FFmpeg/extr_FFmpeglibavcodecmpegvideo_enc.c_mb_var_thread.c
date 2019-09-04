#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_11__ {int mb_var_sum_temp; } ;
struct TYPE_10__ {int* mb_var; int* mb_mean; } ;
struct TYPE_9__ {int (* pix_sum ) (int /*<<< orphan*/ *,int) ;unsigned int (* pix_norm1 ) (int /*<<< orphan*/ *,int) ;} ;
struct TYPE_8__ {TYPE_1__* f; } ;
struct TYPE_12__ {int start_mb_y; int end_mb_y; int mb_width; int linesize; int mb_stride; TYPE_5__ me; TYPE_4__ current_picture; TYPE_3__ mpvencdsp; TYPE_2__ new_picture; } ;
struct TYPE_7__ {int /*<<< orphan*/ ** data; } ;
typedef  TYPE_6__ MpegEncContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_check_alignment () ; 
 int stub1 (int /*<<< orphan*/ *,int) ; 
 unsigned int stub2 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mb_var_thread(AVCodecContext *c, void *arg){
    MpegEncContext *s= *(void**)arg;
    int mb_x, mb_y;

    ff_check_alignment();

    for(mb_y=s->start_mb_y; mb_y < s->end_mb_y; mb_y++) {
        for(mb_x=0; mb_x < s->mb_width; mb_x++) {
            int xx = mb_x * 16;
            int yy = mb_y * 16;
            uint8_t *pix = s->new_picture.f->data[0] + (yy * s->linesize) + xx;
            int varc;
            int sum = s->mpvencdsp.pix_sum(pix, s->linesize);

            varc = (s->mpvencdsp.pix_norm1(pix, s->linesize) -
                    (((unsigned) sum * sum) >> 8) + 500 + 128) >> 8;

            s->current_picture.mb_var [s->mb_stride * mb_y + mb_x] = varc;
            s->current_picture.mb_mean[s->mb_stride * mb_y + mb_x] = (sum+128)>>8;
            s->me.mb_var_sum_temp    += varc;
        }
    }
    return 0;
}