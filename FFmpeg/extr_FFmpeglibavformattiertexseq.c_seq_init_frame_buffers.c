#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int data_size; int /*<<< orphan*/  data; scalar_t__ fill_size; } ;
typedef  TYPE_1__ TiertexSeqFrameBuffer ;
struct TYPE_5__ {int frame_buffers_count; TYPE_1__* frame_buffers; } ;
typedef  TYPE_2__ SeqDemuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SEQ_NUM_FRAME_BUFFERS ; 
 int /*<<< orphan*/  av_malloc (int) ; 
 int avio_rl16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int seq_init_frame_buffers(SeqDemuxContext *seq, AVIOContext *pb)
{
    int i, sz;
    TiertexSeqFrameBuffer *seq_buffer;

    avio_seek(pb, 256, SEEK_SET);

    for (i = 0; i < SEQ_NUM_FRAME_BUFFERS; i++) {
        sz = avio_rl16(pb);
        if (sz == 0)
            break;
        else {
            seq_buffer = &seq->frame_buffers[i];
            seq_buffer->fill_size = 0;
            seq_buffer->data_size = sz;
            seq_buffer->data = av_malloc(sz);
            if (!seq_buffer->data)
                return AVERROR(ENOMEM);
        }
    }
    seq->frame_buffers_count = i;
    return 0;
}