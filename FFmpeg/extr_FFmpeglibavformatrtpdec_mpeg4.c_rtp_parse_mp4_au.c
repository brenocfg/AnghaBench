#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct AUHeaders {int dummy; } ;
struct TYPE_6__ {void* index; void* size; } ;
struct TYPE_5__ {int au_headers_length_bytes; int sizelength; int indexlength; int nb_au_headers; int au_headers_allocated; TYPE_3__* au_headers; } ;
typedef  TYPE_1__ PayloadContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AV_RB16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int RTP_MAX_PACKET_LENGTH ; 
 int /*<<< orphan*/  av_free (TYPE_3__*) ; 
 TYPE_3__* av_malloc (int) ; 
 void* get_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int rtp_parse_mp4_au(PayloadContext *data, const uint8_t *buf, int len)
{
    int au_headers_length, au_header_size, i;
    GetBitContext getbitcontext;

    if (len < 2)
        return AVERROR_INVALIDDATA;

    /* decode the first 2 bytes where the AUHeader sections are stored
       length in bits */
    au_headers_length = AV_RB16(buf);

    if (au_headers_length > RTP_MAX_PACKET_LENGTH)
      return -1;

    data->au_headers_length_bytes = (au_headers_length + 7) / 8;

    /* skip AU headers length section (2 bytes) */
    buf += 2;
    len -= 2;

    if (len < data->au_headers_length_bytes)
        return AVERROR_INVALIDDATA;

    init_get_bits(&getbitcontext, buf, data->au_headers_length_bytes * 8);

    /* XXX: Wrong if optional additional sections are present (cts, dts etc...) */
    au_header_size = data->sizelength + data->indexlength;
    if (au_header_size <= 0 || (au_headers_length % au_header_size != 0))
        return -1;

    data->nb_au_headers = au_headers_length / au_header_size;
    if (!data->au_headers || data->au_headers_allocated < data->nb_au_headers) {
        av_free(data->au_headers);
        data->au_headers = av_malloc(sizeof(struct AUHeaders) * data->nb_au_headers);
        if (!data->au_headers)
            return AVERROR(ENOMEM);
        data->au_headers_allocated = data->nb_au_headers;
    }

    for (i = 0; i < data->nb_au_headers; ++i) {
        data->au_headers[i].size  = get_bits_long(&getbitcontext, data->sizelength);
        data->au_headers[i].index = get_bits_long(&getbitcontext, data->indexlength);
    }

    return 0;
}