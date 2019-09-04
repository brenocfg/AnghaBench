#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_12__ {TYPE_2__* ctx; } ;
struct TYPE_11__ {int /*<<< orphan*/  time_base; scalar_t__ start; } ;
struct TYPE_10__ {int /*<<< orphan*/  time_base; } ;
struct TYPE_9__ {int nb_chapters; TYPE_4__** chapters; } ;
struct TYPE_8__ {size_t file_index; int forced_kf_count; scalar_t__* forced_kf_pts; } ;
typedef  TYPE_1__ OutputStream ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ AVCodecContext ;
typedef  TYPE_4__ AVChapter ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int INT_MAX ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__* av_malloc_array (int,int) ; 
 scalar_t__* av_realloc_f (scalar_t__*,int,int) ; 
 scalar_t__ av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compare_int64 ; 
 int /*<<< orphan*/  exit_program (int) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 TYPE_7__** output_files ; 
 scalar_t__ parse_time_or_die (char*,char*,int) ; 
 int /*<<< orphan*/  qsort (scalar_t__*,int,int,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void parse_forced_key_frames(char *kf, OutputStream *ost,
                                    AVCodecContext *avctx)
{
    char *p;
    int n = 1, i, size, index = 0;
    int64_t t, *pts;

    for (p = kf; *p; p++)
        if (*p == ',')
            n++;
    size = n;
    pts = av_malloc_array(size, sizeof(*pts));
    if (!pts) {
        av_log(NULL, AV_LOG_FATAL, "Could not allocate forced key frames array.\n");
        exit_program(1);
    }

    p = kf;
    for (i = 0; i < n; i++) {
        char *next = strchr(p, ',');

        if (next)
            *next++ = 0;

        if (!memcmp(p, "chapters", 8)) {

            AVFormatContext *avf = output_files[ost->file_index]->ctx;
            int j;

            if (avf->nb_chapters > INT_MAX - size ||
                !(pts = av_realloc_f(pts, size += avf->nb_chapters - 1,
                                     sizeof(*pts)))) {
                av_log(NULL, AV_LOG_FATAL,
                       "Could not allocate forced key frames array.\n");
                exit_program(1);
            }
            t = p[8] ? parse_time_or_die("force_key_frames", p + 8, 1) : 0;
            t = av_rescale_q(t, AV_TIME_BASE_Q, avctx->time_base);

            for (j = 0; j < avf->nb_chapters; j++) {
                AVChapter *c = avf->chapters[j];
                av_assert1(index < size);
                pts[index++] = av_rescale_q(c->start, c->time_base,
                                            avctx->time_base) + t;
            }

        } else {

            t = parse_time_or_die("force_key_frames", p, 1);
            av_assert1(index < size);
            pts[index++] = av_rescale_q(t, AV_TIME_BASE_Q, avctx->time_base);

        }

        p = next;
    }

    av_assert0(index == size);
    qsort(pts, size, sizeof(*pts), compare_int64);
    ost->forced_kf_count = size;
    ost->forced_kf_pts   = pts;
}