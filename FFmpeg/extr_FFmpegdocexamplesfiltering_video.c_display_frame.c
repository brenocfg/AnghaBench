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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int64_t ;
struct TYPE_3__ {scalar_t__ pts; int height; int width; int /*<<< orphan*/ * linesize; int /*<<< orphan*/ ** data; } ;
typedef  int /*<<< orphan*/  AVRational ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ last_pts ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void display_frame(const AVFrame *frame, AVRational time_base)
{
    int x, y;
    uint8_t *p0, *p;
    int64_t delay;

    if (frame->pts != AV_NOPTS_VALUE) {
        if (last_pts != AV_NOPTS_VALUE) {
            /* sleep roughly the right amount of time;
             * usleep is in microseconds, just like AV_TIME_BASE. */
            delay = av_rescale_q(frame->pts - last_pts,
                                 time_base, AV_TIME_BASE_Q);
            if (delay > 0 && delay < 1000000)
                usleep(delay);
        }
        last_pts = frame->pts;
    }

    /* Trivial ASCII grayscale display. */
    p0 = frame->data[0];
    puts("\033c");
    for (y = 0; y < frame->height; y++) {
        p = p0;
        for (x = 0; x < frame->width; x++)
            putchar(" .-+#"[*(p++) / 52]);
        putchar('\n');
        p0 += frame->linesize[0];
    }
    fflush(stdout);
}