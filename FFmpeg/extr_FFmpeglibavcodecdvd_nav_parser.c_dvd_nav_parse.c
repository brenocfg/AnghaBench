#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_7__ {int num; int den; } ;
struct TYPE_10__ {TYPE_1__ time_base; } ;
struct TYPE_9__ {void* duration; int /*<<< orphan*/  pts; int /*<<< orphan*/  pict_type; TYPE_2__* priv_data; } ;
struct TYPE_8__ {void* lba; int* buffer; int copied; } ;
typedef  TYPE_2__ DVDNavParseContext ;
typedef  TYPE_3__ AVCodecParserContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PICTURE_TYPE_NONE ; 
 void* AV_RB32 (int const*) ; 
 int DSI_SIZE ; 
 int PCI_SIZE ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

__attribute__((used)) static int dvd_nav_parse(AVCodecParserContext *s,
                         AVCodecContext *avctx,
                         const uint8_t **poutbuf, int *poutbuf_size,
                         const uint8_t *buf, int buf_size)
{
    DVDNavParseContext *pc1 = s->priv_data;
    int lastPacket          = 0;
    int valid               = 0;

    s->pict_type = AV_PICTURE_TYPE_NONE;

    avctx->time_base.num = 1;
    avctx->time_base.den = 90000;

    if (buf && buf_size) {
        switch(buf[0]) {
            case 0x00:
                if (buf_size == PCI_SIZE) {
                    /* PCI */
                    uint32_t lba      = AV_RB32(&buf[0x01]);
                    uint32_t startpts = AV_RB32(&buf[0x0D]);
                    uint32_t endpts   = AV_RB32(&buf[0x11]);

                    if (endpts > startpts) {
                        pc1->lba    = lba;
                        s->pts      = (int64_t)startpts;
                        s->duration = endpts - startpts;

                        memcpy(pc1->buffer, buf, PCI_SIZE);
                        pc1->copied = PCI_SIZE;
                        valid       = 1;
                    }
                }
                break;

            case 0x01:
                if ((buf_size == DSI_SIZE) && (pc1->copied == PCI_SIZE)) {
                    /* DSI */
                    uint32_t lba = AV_RB32(&buf[0x05]);

                    if (lba == pc1->lba) {
                        memcpy(pc1->buffer + pc1->copied, buf, DSI_SIZE);
                        lastPacket  = 1;
                        valid       = 1;
                    }
                }
                break;
        }
    }

    if (!valid || lastPacket) {
        pc1->copied = 0;
        pc1->lba    = 0xFFFFFFFF;
    }

    if (lastPacket) {
        *poutbuf      = pc1->buffer;
        *poutbuf_size = sizeof(pc1->buffer);
    } else {
        *poutbuf      = NULL;
        *poutbuf_size = 0;
    }

    return buf_size;
}