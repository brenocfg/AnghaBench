#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct AVFormatContext {TYPE_1__* priv_data; int /*<<< orphan*/ * pb; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {scalar_t__ continue_pes; } ;
typedef  TYPE_1__ PVAContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 scalar_t__ FFMIN (scalar_t__,scalar_t__) ; 
 int PVA_MAX_PAYLOAD_LENGTH ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 
 scalar_t__ read_part_of_packet (struct AVFormatContext*,scalar_t__*,int*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t pva_read_timestamp(struct AVFormatContext *s, int stream_index,
                                          int64_t *pos, int64_t pos_limit) {
    AVIOContext *pb = s->pb;
    PVAContext *pvactx = s->priv_data;
    int length, streamid;
    int64_t res = AV_NOPTS_VALUE;

    pos_limit = FFMIN(*pos+PVA_MAX_PAYLOAD_LENGTH*8, (uint64_t)*pos+pos_limit);

    while (*pos < pos_limit) {
        res = AV_NOPTS_VALUE;
        avio_seek(pb, *pos, SEEK_SET);

        pvactx->continue_pes = 0;
        if (read_part_of_packet(s, &res, &length, &streamid, 0)) {
            (*pos)++;
            continue;
        }
        if (streamid - 1 != stream_index || res == AV_NOPTS_VALUE) {
            *pos = avio_tell(pb) + length;
            continue;
        }
        break;
    }

    pvactx->continue_pes = 0;
    return res;
}