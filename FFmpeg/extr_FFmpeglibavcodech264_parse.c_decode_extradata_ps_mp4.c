#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int /*<<< orphan*/  PutByteContext ;
typedef  int /*<<< orphan*/  H264ParamSets ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_EF_EXPLODE ; 
 int AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_WB16 (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ERANGE ; 
 int INT16_MAX ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  const* av_mallocz (int) ; 
 int /*<<< orphan*/  bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  bytestream2_init_writer (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int bytestream2_peek_be24 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_put_be24 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bytestream2_put_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int bytestream2_tell_p (int /*<<< orphan*/ *) ; 
 int decode_extradata_ps (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int,void*) ; 

__attribute__((used)) static int decode_extradata_ps_mp4(const uint8_t *buf, int buf_size, H264ParamSets *ps,
                                   int err_recognition, void *logctx)
{
    int ret;

    ret = decode_extradata_ps(buf, buf_size, ps, 1, logctx);
    if (ret < 0 && !(err_recognition & AV_EF_EXPLODE)) {
        GetByteContext gbc;
        PutByteContext pbc;
        uint8_t *escaped_buf;
        int escaped_buf_size;

        av_log(logctx, AV_LOG_WARNING,
               "SPS decoding failure, trying again after escaping the NAL\n");

        if (buf_size / 2 >= (INT16_MAX - AV_INPUT_BUFFER_PADDING_SIZE) / 3)
            return AVERROR(ERANGE);
        escaped_buf_size = buf_size * 3 / 2 + AV_INPUT_BUFFER_PADDING_SIZE;
        escaped_buf = av_mallocz(escaped_buf_size);
        if (!escaped_buf)
            return AVERROR(ENOMEM);

        bytestream2_init(&gbc, buf, buf_size);
        bytestream2_init_writer(&pbc, escaped_buf, escaped_buf_size);

        while (bytestream2_get_bytes_left(&gbc)) {
            if (bytestream2_get_bytes_left(&gbc) >= 3 &&
                bytestream2_peek_be24(&gbc) <= 3) {
                bytestream2_put_be24(&pbc, 3);
                bytestream2_skip(&gbc, 2);
            } else
                bytestream2_put_byte(&pbc, bytestream2_get_byte(&gbc));
        }

        escaped_buf_size = bytestream2_tell_p(&pbc);
        AV_WB16(escaped_buf, escaped_buf_size - 2);

        (void)decode_extradata_ps(escaped_buf, escaped_buf_size, ps, 1, logctx);
        // lorex.mp4 decodes ok even with extradata decoding failing
        av_freep(&escaped_buf);
    }

    return 0;
}