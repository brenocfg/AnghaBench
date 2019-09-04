#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_11__ {TYPE_2__** streams; TYPE_3__* priv_data; } ;
struct TYPE_10__ {int* buf_ptr; int* buf; scalar_t__ max_payload_size; int /*<<< orphan*/  cur_timestamp; int /*<<< orphan*/  timestamp; } ;
struct TYPE_9__ {TYPE_1__* codecpar; } ;
struct TYPE_8__ {scalar_t__ format; scalar_t__ color_range; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_3__ RTPMuxContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVCOL_RANGE_JPEG ; 
 int AV_CEIL_RSHIFT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_PIX_FMT_YUV420P ; 
 scalar_t__ AV_PIX_FMT_YUV422P ; 
 scalar_t__ AV_PIX_FMT_YUVJ420P ; 
 scalar_t__ AV_PIX_FMT_YUVJ422P ; 
 int AV_RB16 (int const*) ; 
 int const DHT ; 
 int const DQT ; 
 int const EOI ; 
 int FFMIN (int,scalar_t__) ; 
 int const SOF0 ; 
 int const SOS ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avpriv_mjpeg_bits_ac_chrominance ; 
 int /*<<< orphan*/  avpriv_mjpeg_bits_ac_luminance ; 
 int /*<<< orphan*/  avpriv_mjpeg_bits_dc_chrominance ; 
 int /*<<< orphan*/  avpriv_mjpeg_bits_dc_luminance ; 
 int /*<<< orphan*/  avpriv_mjpeg_val_ac_chrominance ; 
 int /*<<< orphan*/  avpriv_mjpeg_val_ac_luminance ; 
 int /*<<< orphan*/  avpriv_mjpeg_val_dc ; 
 int /*<<< orphan*/  bytestream_put_be16 (int**,int) ; 
 int /*<<< orphan*/  bytestream_put_be24 (int**,int) ; 
 int /*<<< orphan*/  bytestream_put_buffer (int**,int const*,int) ; 
 int /*<<< orphan*/  bytestream_put_byte (int**,int) ; 
 int /*<<< orphan*/  ff_rtp_send_data (TYPE_4__*,int*,int,int) ; 
 int /*<<< orphan*/  memcmp (int const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

void ff_rtp_send_jpeg(AVFormatContext *s1, const uint8_t *buf, int size)
{
    RTPMuxContext *s = s1->priv_data;
    const uint8_t *qtables[4] = { NULL };
    int nb_qtables = 0;
    uint8_t type;
    uint8_t w, h;
    uint8_t *p;
    int off = 0; /* fragment offset of the current JPEG frame */
    int len;
    int i;
    int default_huffman_tables = 0;

    s->buf_ptr   = s->buf;
    s->timestamp = s->cur_timestamp;

    /* convert video pixel dimensions from pixels to blocks */
    w = AV_CEIL_RSHIFT(s1->streams[0]->codecpar->width, 3);
    h = AV_CEIL_RSHIFT(s1->streams[0]->codecpar->height, 3);

    /* get the pixel format type or fail */
    if (s1->streams[0]->codecpar->format == AV_PIX_FMT_YUVJ422P ||
        (s1->streams[0]->codecpar->color_range == AVCOL_RANGE_JPEG &&
         s1->streams[0]->codecpar->format == AV_PIX_FMT_YUV422P)) {
        type = 0;
    } else if (s1->streams[0]->codecpar->format == AV_PIX_FMT_YUVJ420P ||
               (s1->streams[0]->codecpar->color_range == AVCOL_RANGE_JPEG &&
                s1->streams[0]->codecpar->format == AV_PIX_FMT_YUV420P)) {
        type = 1;
    } else {
        av_log(s1, AV_LOG_ERROR, "Unsupported pixel format\n");
        return;
    }

    /* preparse the header for getting some info */
    for (i = 0; i < size; i++) {
        if (buf[i] != 0xff)
            continue;

        if (buf[i + 1] == DQT) {
            int tables, j;
            if (buf[i + 4] & 0xF0)
                av_log(s1, AV_LOG_WARNING,
                       "Only 8-bit precision is supported.\n");

            /* a quantization table is 64 bytes long */
            tables = AV_RB16(&buf[i + 2]) / 65;
            if (i + 5 + tables * 65 > size) {
                av_log(s1, AV_LOG_ERROR, "Too short JPEG header. Aborted!\n");
                return;
            }
            if (nb_qtables + tables > 4) {
                av_log(s1, AV_LOG_ERROR, "Invalid number of quantisation tables\n");
                return;
            }

            for (j = 0; j < tables; j++)
                qtables[nb_qtables + j] = buf + i + 5 + j * 65;
            nb_qtables += tables;
        } else if (buf[i + 1] == SOF0) {
            if (buf[i + 14] != 17 || buf[i + 17] != 17) {
                av_log(s1, AV_LOG_ERROR,
                       "Only 1x1 chroma blocks are supported. Aborted!\n");
                return;
            }
        } else if (buf[i + 1] == DHT) {
            int dht_size = AV_RB16(&buf[i + 2]);
            default_huffman_tables |= 1 << 4;
            i += 3;
            dht_size -= 2;
            if (i + dht_size >= size)
                continue;
            while (dht_size > 0)
                switch (buf[i + 1]) {
                case 0x00:
                    if (   dht_size >= 29
                        && !memcmp(buf + i +  2, avpriv_mjpeg_bits_dc_luminance + 1, 16)
                        && !memcmp(buf + i + 18, avpriv_mjpeg_val_dc, 12)) {
                        default_huffman_tables |= 1;
                        i += 29;
                        dht_size -= 29;
                    } else {
                        i += dht_size;
                        dht_size = 0;
                    }
                    break;
                case 0x01:
                    if (   dht_size >= 29
                        && !memcmp(buf + i +  2, avpriv_mjpeg_bits_dc_chrominance + 1, 16)
                        && !memcmp(buf + i + 18, avpriv_mjpeg_val_dc, 12)) {
                        default_huffman_tables |= 1 << 1;
                        i += 29;
                        dht_size -= 29;
                    } else {
                        i += dht_size;
                        dht_size = 0;
                    }
                    break;
                case 0x10:
                    if (   dht_size >= 179
                        && !memcmp(buf + i +  2, avpriv_mjpeg_bits_ac_luminance   + 1, 16)
                        && !memcmp(buf + i + 18, avpriv_mjpeg_val_ac_luminance, 162)) {
                        default_huffman_tables |= 1 << 2;
                        i += 179;
                        dht_size -= 179;
                    } else {
                        i += dht_size;
                        dht_size = 0;
                    }
                    break;
                case 0x11:
                    if (   dht_size >= 179
                        && !memcmp(buf + i +  2, avpriv_mjpeg_bits_ac_chrominance + 1, 16)
                        && !memcmp(buf + i + 18, avpriv_mjpeg_val_ac_chrominance, 162)) {
                        default_huffman_tables |= 1 << 3;
                        i += 179;
                        dht_size -= 179;
                    } else {
                        i += dht_size;
                        dht_size = 0;
                    }
                    break;
                default:
                    i += dht_size;
                    dht_size = 0;
                    continue;
            }
        } else if (buf[i + 1] == SOS) {
            /* SOS is last marker in the header */
            i += AV_RB16(&buf[i + 2]) + 2;
            if (i > size) {
                av_log(s1, AV_LOG_ERROR,
                       "Insufficient data. Aborted!\n");
                return;
            }
            break;
        }
    }
    if (default_huffman_tables && default_huffman_tables != 31) {
        av_log(s1, AV_LOG_ERROR,
               "RFC 2435 requires standard Huffman tables for jpeg\n");
        return;
    }
    if (nb_qtables && nb_qtables != 2)
        av_log(s1, AV_LOG_WARNING,
               "RFC 2435 suggests two quantization tables, %d provided\n",
               nb_qtables);

    /* skip JPEG header */
    buf  += i;
    size -= i;

    for (i = size - 2; i >= 0; i--) {
        if (buf[i] == 0xff && buf[i + 1] == EOI) {
            /* Remove the EOI marker */
            size = i;
            break;
        }
    }

    p = s->buf_ptr;
    while (size > 0) {
        int hdr_size = 8;

        if (off == 0 && nb_qtables)
            hdr_size += 4 + 64 * nb_qtables;

        /* payload max in one packet */
        len = FFMIN(size, s->max_payload_size - hdr_size);

        /* set main header */
        bytestream_put_byte(&p, 0);
        bytestream_put_be24(&p, off);
        bytestream_put_byte(&p, type);
        bytestream_put_byte(&p, 255);
        bytestream_put_byte(&p, w);
        bytestream_put_byte(&p, h);

        if (off == 0 && nb_qtables) {
            /* set quantization tables header */
            bytestream_put_byte(&p, 0);
            bytestream_put_byte(&p, 0);
            bytestream_put_be16(&p, 64 * nb_qtables);

            for (i = 0; i < nb_qtables; i++)
                bytestream_put_buffer(&p, qtables[i], 64);
        }

        /* copy payload data */
        memcpy(p, buf, len);

        /* marker bit is last packet in frame */
        ff_rtp_send_data(s1, s->buf, len + hdr_size, size == len);

        buf  += len;
        size -= len;
        off  += len;
        p     = s->buf;
    }
}