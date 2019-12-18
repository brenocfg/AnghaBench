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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {void* height; void* width; int /*<<< orphan*/  format; } ;
struct TYPE_5__ {TYPE_2__* codecpar; } ;
typedef  int /*<<< orphan*/  PayloadContext ;
typedef  TYPE_1__ AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  TYPE_2__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV420P ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV422P ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV444P ; 
 int /*<<< orphan*/  ENOMEM ; 
 size_t INT_MAX ; 
 void* atoi (char const*) ; 
 int av_base64_decode (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * av_malloc (size_t) ; 
 int parse_packed_headers (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int xiph_parse_fmtp_pair(AVFormatContext *s,
                                AVStream* stream,
                                PayloadContext *xiph_data,
                                const char *attr, const char *value)
{
    AVCodecParameters *par = stream->codecpar;
    int result = 0;

    if (!strcmp(attr, "sampling")) {
        if (!strcmp(value, "YCbCr-4:2:0")) {
            par->format = AV_PIX_FMT_YUV420P;
        } else if (!strcmp(value, "YCbCr-4:4:2")) {
            par->format = AV_PIX_FMT_YUV422P;
        } else if (!strcmp(value, "YCbCr-4:4:4")) {
            par->format = AV_PIX_FMT_YUV444P;
        } else {
            av_log(s, AV_LOG_ERROR,
                   "Unsupported pixel format %s\n", attr);
            return AVERROR_INVALIDDATA;
        }
    } else if (!strcmp(attr, "width")) {
        /* This is an integer between 1 and 1048561
         * and MUST be in multiples of 16. */
        par->width = atoi(value);
        return 0;
    } else if (!strcmp(attr, "height")) {
        /* This is an integer between 1 and 1048561
         * and MUST be in multiples of 16. */
        par->height = atoi(value);
        return 0;
    } else if (!strcmp(attr, "delivery-method")) {
        /* Possible values are: inline, in_band, out_band/specific_name. */
        return AVERROR_PATCHWELCOME;
    } else if (!strcmp(attr, "configuration-uri")) {
        /* NOTE: configuration-uri is supported only under 2 conditions:
         *--after the delivery-method tag
         * --with a delivery-method value of out_band */
        return AVERROR_PATCHWELCOME;
    } else if (!strcmp(attr, "configuration")) {
        /* NOTE: configuration is supported only AFTER the delivery-method tag
         * The configuration value is a base64 encoded packed header */
        uint8_t *decoded_packet = NULL;
        int packet_size;
        size_t decoded_alloc = strlen(value) / 4 * 3 + 4;

        if (decoded_alloc <= INT_MAX) {
            decoded_packet = av_malloc(decoded_alloc);
            if (decoded_packet) {
                packet_size =
                    av_base64_decode(decoded_packet, value, decoded_alloc);

                result = parse_packed_headers
                    (s, decoded_packet, decoded_packet + packet_size, par,
                    xiph_data);
            } else {
                av_log(s, AV_LOG_ERROR,
                       "Out of memory while decoding SDP configuration.\n");
                result = AVERROR(ENOMEM);
            }
        } else {
            av_log(s, AV_LOG_ERROR, "Packet too large\n");
            result = AVERROR_INVALIDDATA;
        }
        av_free(decoded_packet);
    }
    return result;
}