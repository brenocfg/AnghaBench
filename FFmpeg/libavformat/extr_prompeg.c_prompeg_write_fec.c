#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_7__ {TYPE_3__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_9__ {int l; scalar_t__ d; int /*<<< orphan*/  rtp_buf_size; TYPE_1__* fec_row_hd; TYPE_1__* fec_col_hd; int /*<<< orphan*/  length_recovery; int /*<<< orphan*/  rtp_row_sn; int /*<<< orphan*/  rtp_col_sn; scalar_t__* rtp_buf; } ;
struct TYPE_8__ {int /*<<< orphan*/  sn; int /*<<< orphan*/  ts; scalar_t__* bitstring; } ;
typedef  TYPE_2__ PrompegFec ;
typedef  TYPE_3__ PrompegContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_WB16 (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_WB32 (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ PROMPEG_FEC_COL ; 
 scalar_t__ PROMPEG_RTP_PT ; 
 int ffurl_write (TYPE_1__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prompeg_write_fec(URLContext *h, PrompegFec *fec, uint8_t type) {
    PrompegContext *s = h->priv_data;
    URLContext *hd;
    uint8_t *buf = s->rtp_buf; // zero-filled
    uint8_t *b = fec->bitstring;
    uint16_t sn;
    int ret;

    sn = type == PROMPEG_FEC_COL ? ++s->rtp_col_sn : ++s->rtp_row_sn;

    // V, P, X, CC
    buf[0] = 0x80 | (b[0] & 0x3f);
    // M, PT
    buf[1] = (b[1] & 0x80) | PROMPEG_RTP_PT;
    // SN
    AV_WB16(buf + 2, sn);
    // TS
    AV_WB32(buf + 4, fec->ts);
    // CSRC=0
    //AV_WB32(buf + 8, 0);
    // SNBase low bits
    AV_WB16(buf + 12, fec->sn);
    // Length recovery
    buf[14] = b[6];
    buf[15] = b[7];
    // E=1, PT recovery
    buf[16] = 0x80 | b[1];
    // Mask=0
    //buf[17] = 0x0;
    //buf[18] = 0x0;
    //buf[19] = 0x0;
    // TS recovery
    buf[20] = b[2];
    buf[21] = b[3];
    buf[22] = b[4];
    buf[23] = b[5];
    // X=0, D, type=0, index=0
    buf[24] = type == PROMPEG_FEC_COL ? 0x0 : 0x40;
    // offset
    buf[25] = type == PROMPEG_FEC_COL ? s->l : 0x1;
    // NA
    buf[26] = type == PROMPEG_FEC_COL ? s->d : s->l;
    // SNBase ext bits=0
    //buf[27] = 0x0;
    // Payload
    memcpy(buf + 28, b + 8, s->length_recovery);

    hd = type == PROMPEG_FEC_COL ? s->fec_col_hd : s->fec_row_hd;
    ret = ffurl_write(hd, buf, s->rtp_buf_size);
    return ret;
}