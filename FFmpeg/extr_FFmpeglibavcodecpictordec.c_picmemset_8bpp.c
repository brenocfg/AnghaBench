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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_5__ {int width; } ;
typedef  TYPE_1__ PicContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void picmemset_8bpp(PicContext *s, AVFrame *frame, int value, int run,
                           int *x, int *y)
{
    while (run > 0) {
        uint8_t *d = frame->data[0] + *y * frame->linesize[0];
        if (*x + run >= s->width) {
            int n = s->width - *x;
            memset(d + *x, value, n);
            run -= n;
            *x = 0;
            *y -= 1;
            if (*y < 0)
                break;
        } else {
            memset(d + *x, value, run);
            *x += run;
            break;
        }
    }
}