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
struct TYPE_3__ {int nb_filters; int /*<<< orphan*/ * filters; int /*<<< orphan*/ * filter_frame; } ;
typedef  TYPE_1__ InputStream ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int av_frame_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ifilter_send_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int send_frame_to_filters(InputStream *ist, AVFrame *decoded_frame)
{
    int i, ret;
    AVFrame *f;

    av_assert1(ist->nb_filters > 0); /* ensure ret is initialized */
    for (i = 0; i < ist->nb_filters; i++) {
        if (i < ist->nb_filters - 1) {
            f = ist->filter_frame;
            ret = av_frame_ref(f, decoded_frame);
            if (ret < 0)
                break;
        } else
            f = decoded_frame;
        ret = ifilter_send_frame(ist->filters[i], f);
        if (ret == AVERROR_EOF)
            ret = 0; /* ignore */
        if (ret < 0) {
            av_log(NULL, AV_LOG_ERROR,
                   "Failed to inject frame into filter network: %s\n", av_err2str(ret));
            break;
        }
    }
    return ret;
}