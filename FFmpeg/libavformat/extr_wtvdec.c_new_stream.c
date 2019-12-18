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
typedef  int /*<<< orphan*/  WtvStream ;
struct TYPE_8__ {int id; int /*<<< orphan*/  need_parsing; TYPE_1__* codecpar; int /*<<< orphan*/ * priv_data; } ;
struct TYPE_7__ {int codec_type; scalar_t__ extradata_size; scalar_t__ extradata; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVSTREAM_PARSE_FULL ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (scalar_t__*) ; 
 int /*<<< orphan*/ * av_mallocz (int) ; 
 TYPE_2__* avformat_new_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int,int) ; 

__attribute__((used)) static AVStream * new_stream(AVFormatContext *s, AVStream *st, int sid, int codec_type)
{
    if (st) {
        if (st->codecpar->extradata) {
            av_freep(&st->codecpar->extradata);
            st->codecpar->extradata_size = 0;
        }
    } else {
        WtvStream *wst = av_mallocz(sizeof(WtvStream));
        if (!wst)
            return NULL;
        st = avformat_new_stream(s, NULL);
        if (!st) {
            av_free(wst);
            return NULL;
        }
        st->id = sid;
        st->priv_data = wst;
    }
    st->codecpar->codec_type = codec_type;
    st->need_parsing      = AVSTREAM_PARSE_FULL;
    avpriv_set_pts_info(st, 64, 1, 10000000);
    return st;
}