#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_8__ {TYPE_1__* priv_data; } ;
struct TYPE_7__ {scalar_t__ eof; int /*<<< orphan*/ * cur_file; TYPE_2__* avf; } ;
typedef  int /*<<< orphan*/  ConcatFile ;
typedef  TYPE_1__ ConcatContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVSEEK_FLAG_BYTE ; 
 int AVSEEK_FLAG_FRAME ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  avformat_close_input (TYPE_2__**) ; 
 int real_seek (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_2__*) ; 

__attribute__((used)) static int concat_seek(AVFormatContext *avf, int stream,
                       int64_t min_ts, int64_t ts, int64_t max_ts, int flags)
{
    ConcatContext *cat = avf->priv_data;
    ConcatFile *cur_file_saved = cat->cur_file;
    AVFormatContext *cur_avf_saved = cat->avf;
    int ret;

    if (flags & (AVSEEK_FLAG_BYTE | AVSEEK_FLAG_FRAME))
        return AVERROR(ENOSYS);
    cat->avf = NULL;
    if ((ret = real_seek(avf, stream, min_ts, ts, max_ts, flags, cur_avf_saved)) < 0) {
        if (cat->cur_file != cur_file_saved) {
            if (cat->avf)
                avformat_close_input(&cat->avf);
        }
        cat->avf      = cur_avf_saved;
        cat->cur_file = cur_file_saved;
    } else {
        if (cat->cur_file != cur_file_saved) {
            avformat_close_input(&cur_avf_saved);
        }
        cat->eof = 0;
    }
    return ret;
}