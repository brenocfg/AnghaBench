#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {size_t size; scalar_t__ data; } ;
struct TYPE_7__ {size_t size_; scalar_t__ data_; } ;
typedef  TYPE_1__ FuzzDataBuffer ;
typedef  TYPE_2__ AVPacket ;

/* Variables and functions */
 size_t AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  FDBRealloc (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  av_init_packet (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void FDBPrepare(FuzzDataBuffer *FDB, AVPacket *dst, const uint8_t *data,
                size_t size)
{
    FDBRealloc(FDB, size);
    memcpy(FDB->data_, data, size);
    size_t padd = FDB->size_ - size;
    if (padd > AV_INPUT_BUFFER_PADDING_SIZE)
        padd = AV_INPUT_BUFFER_PADDING_SIZE;
    memset(FDB->data_ + size, 0, padd);
    av_init_packet(dst);
    dst->data = FDB->data_;
    dst->size = size;
}