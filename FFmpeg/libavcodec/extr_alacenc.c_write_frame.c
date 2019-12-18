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
typedef  size_t uint8_t ;
typedef  enum AlacRawDataBlockType { ____Placeholder_AlacRawDataBlockType } AlacRawDataBlockType ;
struct TYPE_9__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {TYPE_1__* avctx; int /*<<< orphan*/  pbctx; } ;
struct TYPE_7__ {int channels; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_2__ AlacEncodeContext ;
typedef  TYPE_3__ AVPacket ;

/* Variables and functions */
 int const TYPE_CPE ; 
 int /*<<< orphan*/  TYPE_END ; 
 int const TYPE_SCE ; 
 int** ff_alac_channel_elements ; 
 size_t** ff_alac_channel_layout_offsets ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int put_bits_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_element (TYPE_2__*,int const,int,size_t* const,size_t* const) ; 

__attribute__((used)) static int write_frame(AlacEncodeContext *s, AVPacket *avpkt,
                       uint8_t * const *samples)
{
    PutBitContext *pb = &s->pbctx;
    const enum AlacRawDataBlockType *ch_elements = ff_alac_channel_elements[s->avctx->channels - 1];
    const uint8_t *ch_map = ff_alac_channel_layout_offsets[s->avctx->channels - 1];
    int ch, element, sce, cpe;

    init_put_bits(pb, avpkt->data, avpkt->size);

    ch = element = sce = cpe = 0;
    while (ch < s->avctx->channels) {
        if (ch_elements[element] == TYPE_CPE) {
            write_element(s, TYPE_CPE, cpe, samples[ch_map[ch]],
                          samples[ch_map[ch + 1]]);
            cpe++;
            ch += 2;
        } else {
            write_element(s, TYPE_SCE, sce, samples[ch_map[ch]], NULL);
            sce++;
            ch++;
        }
        element++;
    }

    put_bits(pb, 3, TYPE_END);
    flush_put_bits(pb);

    return put_bits_count(pb) >> 3;
}