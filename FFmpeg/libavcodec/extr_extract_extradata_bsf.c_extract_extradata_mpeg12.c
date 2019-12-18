#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_8__ {TYPE_1__* priv_data; } ;
struct TYPE_7__ {int size; int* data; } ;
struct TYPE_6__ {scalar_t__ remove; } ;
typedef  TYPE_1__ ExtractExtradataContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVBSFContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int UINT32_MAX ; 
 int /*<<< orphan*/ * av_malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int extract_extradata_mpeg12(AVBSFContext *ctx, AVPacket *pkt,
                                     uint8_t **data, int *size)
{
    ExtractExtradataContext *s = ctx->priv_data;
    uint32_t state = UINT32_MAX;
    int i, found = 0;

    for (i = 0; i < pkt->size; i++) {
        state = (state << 8) | pkt->data[i];
        if (state == 0x1B3)
            found = 1;
        else if (found && state != 0x1B5 && state < 0x200 && state >= 0x100) {
            if (i > 3) {
                *size = i - 3;
                *data = av_malloc(*size + AV_INPUT_BUFFER_PADDING_SIZE);
                if (!*data)
                    return AVERROR(ENOMEM);

                memcpy(*data, pkt->data, *size);
                memset(*data + *size, 0, AV_INPUT_BUFFER_PADDING_SIZE);

                if (s->remove) {
                    pkt->data += *size;
                    pkt->size -= *size;
                }
            }
            break;
        }
    }
    return 0;
}