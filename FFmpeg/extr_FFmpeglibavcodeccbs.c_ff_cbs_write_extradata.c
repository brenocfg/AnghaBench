#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ extradata_size; scalar_t__ extradata; } ;
struct TYPE_6__ {scalar_t__ data_size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ CodedBitstreamFragment ;
typedef  int /*<<< orphan*/  CodedBitstreamContext ;
typedef  TYPE_2__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_freep (scalar_t__*) ; 
 scalar_t__ av_malloc (scalar_t__) ; 
 int ff_cbs_write_fragment_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

int ff_cbs_write_extradata(CodedBitstreamContext *ctx,
                           AVCodecParameters *par,
                           CodedBitstreamFragment *frag)
{
    int err;

    err = ff_cbs_write_fragment_data(ctx, frag);
    if (err < 0)
        return err;

    av_freep(&par->extradata);

    par->extradata = av_malloc(frag->data_size +
                               AV_INPUT_BUFFER_PADDING_SIZE);
    if (!par->extradata)
        return AVERROR(ENOMEM);

    memcpy(par->extradata, frag->data, frag->data_size);
    memset(par->extradata + frag->data_size, 0,
           AV_INPUT_BUFFER_PADDING_SIZE);
    par->extradata_size = frag->data_size;

    return 0;
}