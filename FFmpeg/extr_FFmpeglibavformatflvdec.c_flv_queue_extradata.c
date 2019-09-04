#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* new_extradata_size; int /*<<< orphan*/ * new_extradata; } ;
typedef  TYPE_1__ FLVContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_mallocz (scalar_t__) ; 
 int /*<<< orphan*/  avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int flv_queue_extradata(FLVContext *flv, AVIOContext *pb, int stream,
                               int size)
{
    if (!size)
        return 0;

    av_free(flv->new_extradata[stream]);
    flv->new_extradata[stream] = av_mallocz(size +
                                            AV_INPUT_BUFFER_PADDING_SIZE);
    if (!flv->new_extradata[stream])
        return AVERROR(ENOMEM);
    flv->new_extradata_size[stream] = size;
    avio_read(pb, flv->new_extradata[stream], size);
    return 0;
}