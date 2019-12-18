#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_7__ {int* data; } ;
struct TYPE_6__ {int nb_units; int* data; size_t data_size; TYPE_1__* units; TYPE_4__* data_ref; } ;
struct TYPE_5__ {scalar_t__ data_size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ CodedBitstreamUnit ;
typedef  TYPE_2__ CodedBitstreamFragment ;
typedef  int /*<<< orphan*/  CodedBitstreamContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 TYPE_4__* av_buffer_alloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int cbs_mpeg2_assemble_fragment(CodedBitstreamContext *ctx,
                                       CodedBitstreamFragment *frag)
{
    uint8_t *data;
    size_t size, dp;
    int i;

    size = 0;
    for (i = 0; i < frag->nb_units; i++)
        size += 3 + frag->units[i].data_size;

    frag->data_ref = av_buffer_alloc(size + AV_INPUT_BUFFER_PADDING_SIZE);
    if (!frag->data_ref)
        return AVERROR(ENOMEM);
    data = frag->data_ref->data;

    dp = 0;
    for (i = 0; i < frag->nb_units; i++) {
        CodedBitstreamUnit *unit = &frag->units[i];

        data[dp++] = 0;
        data[dp++] = 0;
        data[dp++] = 1;

        memcpy(data + dp, unit->data, unit->data_size);
        dp += unit->data_size;
    }

    av_assert0(dp == size);

    memset(data + size, 0, AV_INPUT_BUFFER_PADDING_SIZE);
    frag->data      = data;
    frag->data_size = size;

    return 0;
}