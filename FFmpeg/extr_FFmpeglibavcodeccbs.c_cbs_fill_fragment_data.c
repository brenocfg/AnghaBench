#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {scalar_t__ data; } ;
struct TYPE_4__ {size_t data_size; scalar_t__ data; TYPE_3__* data_ref; } ;
typedef  TYPE_1__ CodedBitstreamFragment ;
typedef  int /*<<< orphan*/  CodedBitstreamContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 TYPE_3__* av_buffer_alloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int cbs_fill_fragment_data(CodedBitstreamContext *ctx,
                                  CodedBitstreamFragment *frag,
                                  const uint8_t *data, size_t size)
{
    av_assert0(!frag->data && !frag->data_ref);

    frag->data_ref =
        av_buffer_alloc(size + AV_INPUT_BUFFER_PADDING_SIZE);
    if (!frag->data_ref)
        return AVERROR(ENOMEM);

    frag->data      = frag->data_ref->data;
    frag->data_size = size;

    memcpy(frag->data, data, size);
    memset(frag->data + size, 0,
           AV_INPUT_BUFFER_PADDING_SIZE);

    return 0;
}