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
typedef  scalar_t__ int64_t ;
struct TYPE_3__ {scalar_t__ next_klv; scalar_t__ length; scalar_t__ key; scalar_t__ offset; } ;
typedef  TYPE_1__ KLVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ INT64_MAX ; 
 int /*<<< orphan*/  avio_read (int /*<<< orphan*/ *,scalar_t__,int) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 
 scalar_t__ klv_decode_ber_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxf_klv_key ; 
 int /*<<< orphan*/  mxf_read_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int klv_read_packet(KLVPacket *klv, AVIOContext *pb)
{
    int64_t length, pos;
    if (!mxf_read_sync(pb, mxf_klv_key, 4))
        return AVERROR_INVALIDDATA;
    klv->offset = avio_tell(pb) - 4;
    memcpy(klv->key, mxf_klv_key, 4);
    avio_read(pb, klv->key + 4, 12);
    length = klv_decode_ber_length(pb);
    if (length < 0)
        return length;
    klv->length = length;
    pos = avio_tell(pb);
    if (pos > INT64_MAX - length)
        return AVERROR_INVALIDDATA;
    klv->next_klv = pos + length;
    return 0;
}