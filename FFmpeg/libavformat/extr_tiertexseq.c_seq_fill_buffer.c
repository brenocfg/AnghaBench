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
struct TYPE_4__ {scalar_t__ fill_size; scalar_t__ data_size; scalar_t__ data; } ;
typedef  TYPE_1__ TiertexSeqFrameBuffer ;
struct TYPE_5__ {scalar_t__ current_frame_offs; TYPE_1__* frame_buffers; } ;
typedef  TYPE_2__ SeqDemuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SEQ_NUM_FRAME_BUFFERS ; 
 int avio_read (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int seq_fill_buffer(SeqDemuxContext *seq, AVIOContext *pb, int buffer_num, unsigned int data_offs, int data_size)
{
    TiertexSeqFrameBuffer *seq_buffer;

    if (buffer_num >= SEQ_NUM_FRAME_BUFFERS)
        return AVERROR_INVALIDDATA;

    seq_buffer = &seq->frame_buffers[buffer_num];
    if (seq_buffer->fill_size + data_size > seq_buffer->data_size || data_size <= 0)
        return AVERROR_INVALIDDATA;

    avio_seek(pb, seq->current_frame_offs + data_offs, SEEK_SET);
    if (avio_read(pb, seq_buffer->data + seq_buffer->fill_size, data_size) != data_size)
        return AVERROR(EIO);

    seq_buffer->fill_size += data_size;
    return 0;
}