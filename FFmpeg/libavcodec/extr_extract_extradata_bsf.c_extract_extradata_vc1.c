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
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_8__ {TYPE_1__* priv_data; } ;
struct TYPE_7__ {int size; int /*<<< orphan*/  const* data; } ;
struct TYPE_6__ {scalar_t__ remove; } ;
typedef  TYPE_1__ ExtractExtradataContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVBSFContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ IS_MARKER (scalar_t__) ; 
 scalar_t__ UINT32_MAX ; 
 scalar_t__ VC1_CODE_ENTRYPOINT ; 
 scalar_t__ VC1_CODE_SEQHDR ; 
 int /*<<< orphan*/  const* av_malloc (scalar_t__) ; 
 int /*<<< orphan*/  const* avpriv_find_start_code (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int extract_extradata_vc1(AVBSFContext *ctx, AVPacket *pkt,
                                 uint8_t **data, int *size)
{
    ExtractExtradataContext *s = ctx->priv_data;
    const uint8_t *ptr = pkt->data, *end = pkt->data + pkt->size;
    uint32_t state = UINT32_MAX;
    int has_extradata = 0, extradata_size = 0;

    while (ptr < end) {
        ptr = avpriv_find_start_code(ptr, end, &state);
        if (state == VC1_CODE_SEQHDR || state == VC1_CODE_ENTRYPOINT) {
            has_extradata = 1;
        } else if (has_extradata && IS_MARKER(state)) {
            extradata_size = ptr - 4 - pkt->data;
            break;
        }
    }

    if (extradata_size) {
        *data = av_malloc(extradata_size + AV_INPUT_BUFFER_PADDING_SIZE);
        if (!*data)
            return AVERROR(ENOMEM);

        memcpy(*data, pkt->data, extradata_size);
        memset(*data + extradata_size, 0, AV_INPUT_BUFFER_PADDING_SIZE);
        *size = extradata_size;

        if (s->remove) {
            pkt->data += extradata_size;
            pkt->size -= extradata_size;
        }
    }

    return 0;
}