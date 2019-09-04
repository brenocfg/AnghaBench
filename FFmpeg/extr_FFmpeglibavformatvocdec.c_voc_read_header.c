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
struct TYPE_5__ {scalar_t__ remaining_size; } ;
typedef  TYPE_1__ VocDecContext ;
struct TYPE_6__ {int /*<<< orphan*/  ctx_flags; int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVFMTCTX_NOHEADER ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 
 int avio_rl16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int voc_read_header(AVFormatContext *s)
{
    VocDecContext *voc = s->priv_data;
    AVIOContext *pb = s->pb;
    int header_size;

    avio_skip(pb, 20);
    header_size = avio_rl16(pb) - 22;
    if (header_size != 4) {
        av_log(s, AV_LOG_ERROR, "unknown header size: %d\n", header_size);
        return AVERROR(ENOSYS);
    }
    avio_skip(pb, header_size);

    s->ctx_flags |= AVFMTCTX_NOHEADER;

    voc->remaining_size = 0;
    return 0;
}