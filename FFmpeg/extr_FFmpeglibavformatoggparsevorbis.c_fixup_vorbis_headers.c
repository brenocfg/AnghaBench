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
typedef  unsigned char uint8_t ;
struct oggvorbis_private {int* len; int /*<<< orphan*/ * packet; } ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 unsigned char* av_realloc (int /*<<< orphan*/ *,int) ; 
 int av_reallocp (unsigned char**,scalar_t__) ; 
 scalar_t__ av_xiphlacing (unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,char,int) ; 

__attribute__((used)) static int fixup_vorbis_headers(AVFormatContext *as,
                                struct oggvorbis_private *priv,
                                uint8_t **buf)
{
    int i, offset, len, err;
    int buf_len;
    unsigned char *ptr;

    len = priv->len[0] + priv->len[1] + priv->len[2];
    buf_len = len + len / 255 + 64;

    if (*buf)
        return AVERROR_INVALIDDATA;

    ptr = *buf = av_realloc(NULL, buf_len);
    if (!ptr)
        return AVERROR(ENOMEM);
    memset(*buf, '\0', buf_len);

    ptr[0]  = 2;
    offset  = 1;
    offset += av_xiphlacing(&ptr[offset], priv->len[0]);
    offset += av_xiphlacing(&ptr[offset], priv->len[1]);
    for (i = 0; i < 3; i++) {
        memcpy(&ptr[offset], priv->packet[i], priv->len[i]);
        offset += priv->len[i];
        av_freep(&priv->packet[i]);
    }
    if ((err = av_reallocp(buf, offset + AV_INPUT_BUFFER_PADDING_SIZE)) < 0)
        return err;
    return offset;
}