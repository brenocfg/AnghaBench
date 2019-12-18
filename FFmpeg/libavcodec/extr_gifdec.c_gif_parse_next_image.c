#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ GifState ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
#define  GIF_EXTENSION_INTRODUCER 130 
#define  GIF_IMAGE_SEPARATOR 129 
#define  GIF_TRAILER 128 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 scalar_t__ bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int gif_read_extension (TYPE_1__*) ; 
 int gif_read_image (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gif_parse_next_image(GifState *s, AVFrame *frame)
{
    while (bytestream2_get_bytes_left(&s->gb) > 0) {
        int code = bytestream2_get_byte(&s->gb);
        int ret;

        av_log(s->avctx, AV_LOG_DEBUG, "code=%02x '%c'\n", code, code);

        switch (code) {
        case GIF_IMAGE_SEPARATOR:
            return gif_read_image(s, frame);
        case GIF_EXTENSION_INTRODUCER:
            if ((ret = gif_read_extension(s)) < 0)
                return ret;
            break;
        case GIF_TRAILER:
            /* end of image */
            return AVERROR_EOF;
        default:
            /* erroneous block label */
            return AVERROR_INVALIDDATA;
        }
    }
    return AVERROR_EOF;
}