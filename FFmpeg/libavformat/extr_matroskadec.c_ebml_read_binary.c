#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_6__ {int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {int size; int /*<<< orphan*/ * data; TYPE_3__* buf; int /*<<< orphan*/  pos; } ;
typedef  TYPE_1__ EbmlBin ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int NEEDS_CHECKING ; 
 int av_buffer_realloc (TYPE_3__**,scalar_t__) ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_3__**) ; 
 int avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ebml_read_binary(AVIOContext *pb, int length,
                            int64_t pos, EbmlBin *bin)
{
    int ret;

    ret = av_buffer_realloc(&bin->buf, length + AV_INPUT_BUFFER_PADDING_SIZE);
    if (ret < 0)
        return ret;
    memset(bin->buf->data + length, 0, AV_INPUT_BUFFER_PADDING_SIZE);

    bin->data = bin->buf->data;
    bin->size = length;
    bin->pos  = pos;
    if ((ret = avio_read(pb, bin->data, length)) != length) {
        av_buffer_unref(&bin->buf);
        bin->data = NULL;
        bin->size = 0;
        return ret < 0 ? ret : NEEDS_CHECKING;
    }

    return 0;
}