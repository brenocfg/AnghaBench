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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_11__ {int /*<<< orphan*/ * data_ref; } ;
struct TYPE_10__ {size_t size; scalar_t__* data; scalar_t__* raw_data; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int /*<<< orphan*/ * rbsp_buffer_ref; } ;
struct TYPE_9__ {int nb_nals; TYPE_1__ rbsp; TYPE_3__* nals; } ;
typedef  TYPE_2__ H2645Packet ;
typedef  TYPE_3__ H2645NAL ;
typedef  TYPE_4__ CodedBitstreamFragment ;
typedef  int /*<<< orphan*/  CodedBitstreamContext ;
typedef  int /*<<< orphan*/  AVBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int) ; 
 int ff_cbs_insert_unit_data (int /*<<< orphan*/ *,TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cbs_h2645_fragment_add_nals(CodedBitstreamContext *ctx,
                                       CodedBitstreamFragment *frag,
                                       const H2645Packet *packet)
{
    int err, i;

    for (i = 0; i < packet->nb_nals; i++) {
        const H2645NAL *nal = &packet->nals[i];
        AVBufferRef *ref;
        size_t size = nal->size;

        // Remove trailing zeroes.
        while (size > 0 && nal->data[size - 1] == 0)
            --size;
        av_assert0(size > 0);

        ref = (nal->data == nal->raw_data) ? frag->data_ref
                                           : packet->rbsp.rbsp_buffer_ref;

        err = ff_cbs_insert_unit_data(ctx, frag, -1, nal->type,
                            (uint8_t*)nal->data, size, ref);
        if (err < 0)
            return err;
    }

    return 0;
}