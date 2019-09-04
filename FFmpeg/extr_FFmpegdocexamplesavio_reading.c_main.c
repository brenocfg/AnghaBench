#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct buffer_data {size_t size; int /*<<< orphan*/ * ptr; int /*<<< orphan*/  member_0; } ;
struct TYPE_11__ {TYPE_1__* pb; } ;
struct TYPE_10__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_dump_format (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* av_err2str (int) ; 
 int av_file_map (char*,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_file_unmap (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * av_malloc (size_t) ; 
 TYPE_2__* avformat_alloc_context () ; 
 int /*<<< orphan*/  avformat_close_input (TYPE_2__**) ; 
 int avformat_find_stream_info (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int avformat_open_input (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* avio_alloc_context (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,struct buffer_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_context_free (TYPE_1__**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  read_packet ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char *argv[])
{
    AVFormatContext *fmt_ctx = NULL;
    AVIOContext *avio_ctx = NULL;
    uint8_t *buffer = NULL, *avio_ctx_buffer = NULL;
    size_t buffer_size, avio_ctx_buffer_size = 4096;
    char *input_filename = NULL;
    int ret = 0;
    struct buffer_data bd = { 0 };

    if (argc != 2) {
        fprintf(stderr, "usage: %s input_file\n"
                "API example program to show how to read from a custom buffer "
                "accessed through AVIOContext.\n", argv[0]);
        return 1;
    }
    input_filename = argv[1];

    /* slurp file content into buffer */
    ret = av_file_map(input_filename, &buffer, &buffer_size, 0, NULL);
    if (ret < 0)
        goto end;

    /* fill opaque structure used by the AVIOContext read callback */
    bd.ptr  = buffer;
    bd.size = buffer_size;

    if (!(fmt_ctx = avformat_alloc_context())) {
        ret = AVERROR(ENOMEM);
        goto end;
    }

    avio_ctx_buffer = av_malloc(avio_ctx_buffer_size);
    if (!avio_ctx_buffer) {
        ret = AVERROR(ENOMEM);
        goto end;
    }
    avio_ctx = avio_alloc_context(avio_ctx_buffer, avio_ctx_buffer_size,
                                  0, &bd, &read_packet, NULL, NULL);
    if (!avio_ctx) {
        ret = AVERROR(ENOMEM);
        goto end;
    }
    fmt_ctx->pb = avio_ctx;

    ret = avformat_open_input(&fmt_ctx, NULL, NULL, NULL);
    if (ret < 0) {
        fprintf(stderr, "Could not open input\n");
        goto end;
    }

    ret = avformat_find_stream_info(fmt_ctx, NULL);
    if (ret < 0) {
        fprintf(stderr, "Could not find stream information\n");
        goto end;
    }

    av_dump_format(fmt_ctx, 0, input_filename, 0);

end:
    avformat_close_input(&fmt_ctx);

    /* note: the internal buffer could have changed, and be != avio_ctx_buffer */
    if (avio_ctx)
        av_freep(&avio_ctx->buffer);
    avio_context_free(&avio_ctx);

    av_file_unmap(buffer, buffer_size);

    if (ret < 0) {
        fprintf(stderr, "Error occurred: %s\n", av_err2str(ret));
        return 1;
    }

    return 0;
}