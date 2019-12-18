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
typedef  scalar_t__ int64_t ;
struct TYPE_3__ {int flags; int (* read_probe ) (int /*<<< orphan*/ *) ;char* name; } ;
typedef  int /*<<< orphan*/  AVProbeData ;
typedef  TYPE_1__ AVInputFormat ;

/* Variables and functions */
 int AVFMT_NOFILE ; 
 int AVPROBE_SCORE_MAX ; 
 scalar_t__ AV_READ_TIME () ; 
 TYPE_1__* av_demuxer_iterate (void**) ; 
 int /*<<< orphan*/  failures ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,int,int,int) ; 
 int* score_array ; 
 int /*<<< orphan*/  single_format ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * time_array ; 

__attribute__((used)) static void probe(AVProbeData *pd, int type, int p, int size)
{
    int i = 0;
    const AVInputFormat *fmt = NULL;
    void *fmt_opaque = NULL;

    while ((fmt = av_demuxer_iterate(&fmt_opaque))) {
        if (fmt->flags & AVFMT_NOFILE)
            continue;
        if (fmt->read_probe &&
            (!single_format || !strcmp(single_format, fmt->name))
        ) {
            int score;
            int64_t start = AV_READ_TIME();
            score = fmt->read_probe(pd);
            time_array[i] += AV_READ_TIME() - start;
            if (score > score_array[i] && score > AVPROBE_SCORE_MAX / 4) {
                score_array[i] = score;
                fprintf(stderr,
                        "Failure of %s probing code with score=%d type=%d p=%X size=%d\n",
                        fmt->name, score, type, p, size);
                failures++;
            }
        }
        i++;
    }
}