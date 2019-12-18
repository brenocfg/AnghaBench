#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int int64_t ;
struct TYPE_15__ {TYPE_2__* pb; } ;
struct TYPE_14__ {struct TYPE_14__* buffer; } ;
struct TYPE_13__ {int filesize; size_t fuzz_size; int /*<<< orphan*/  const* fuzz; scalar_t__ pos; } ;
typedef  TYPE_1__ IOContext ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_2__ AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_PANIC ; 
 int /*<<< orphan*/  FUZZ_TAG ; 
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 int /*<<< orphan*/  av_init_packet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log_set_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * av_malloc (int) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int av_read_frame (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_register_all () ; 
 int /*<<< orphan*/  avcodec_register_all () ; 
 TYPE_3__* avformat_alloc_context () ; 
 int /*<<< orphan*/  avformat_close_input (TYPE_3__**) ; 
 int avformat_find_stream_info (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avformat_free_context (TYPE_3__*) ; 
 int avformat_open_input (TYPE_3__**,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* avio_alloc_context (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le32 (int /*<<< orphan*/ *) ; 
 int bytestream2_get_le64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  io_read ; 
 int /*<<< orphan*/ * io_seek ; 
 scalar_t__ maxiteration ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/  const*,int) ; 

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    const uint64_t fuzz_tag = FUZZ_TAG;
    uint32_t it = 0;
    AVFormatContext *avfmt = avformat_alloc_context();
    AVPacket pkt;
    char filename[1025] = {0};
    AVIOContext *fuzzed_pb = NULL;
    uint8_t *io_buffer;
    int io_buffer_size = 32768;
    int64_t filesize   = size;
    IOContext opaque;
    static int c;
    int seekable = 0;
    int ret;

    if (!c) {
        av_register_all();
        avcodec_register_all();
        av_log_set_level(AV_LOG_PANIC);
        c=1;
    }

    if (!avfmt)
        error("Failed avformat_alloc_context()");

    if (size > 2048) {
        GetByteContext gbc;
        memcpy (filename, data + size - 1024, 1024);
        bytestream2_init(&gbc, data + size - 2048, 1024);
        size -= 2048;

        io_buffer_size = bytestream2_get_le32(&gbc) & 0xFFFFFFF;
        seekable       = bytestream2_get_byte(&gbc) & 1;
        filesize       = bytestream2_get_le64(&gbc) & 0x7FFFFFFFFFFFFFFF;
    }
    io_buffer = av_malloc(io_buffer_size);
    if (!io_buffer)
        error("Failed to allocate io_buffer");

    opaque.filesize = filesize;
    opaque.pos      = 0;
    opaque.fuzz     = data;
    opaque.fuzz_size= size;
    fuzzed_pb = avio_alloc_context(io_buffer, io_buffer_size, 0, &opaque,
                                   io_read, NULL, seekable ? io_seek : NULL);
    if (!fuzzed_pb)
        error("avio_alloc_context failed");

    avfmt->pb = fuzzed_pb;

    ret = avformat_open_input(&avfmt, filename, NULL, NULL);
    if (ret < 0) {
        av_freep(&fuzzed_pb->buffer);
        av_freep(&fuzzed_pb);
        avformat_free_context(avfmt);
        return 0;
    }

    ret = avformat_find_stream_info(avfmt, NULL);

    av_init_packet(&pkt);

    //TODO, test seeking

    for(it = 0; it < maxiteration; it++) {
        ret = av_read_frame(avfmt, &pkt);
        if (ret < 0)
            break;
        av_packet_unref(&pkt);
    }
end:
    av_freep(&fuzzed_pb->buffer);
    av_freep(&fuzzed_pb);
    avformat_close_input(&avfmt);

    return 0;
}