#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int int64_t ;
struct TYPE_16__ {int seekable; } ;
struct TYPE_15__ {TYPE_6__* pb; TYPE_1__* priv_data; } ;
struct TYPE_14__ {int next_klv; int length; int /*<<< orphan*/  key; } ;
struct TYPE_13__ {int run_in; int footer_partition; } ;
typedef  TYPE_1__ MXFContext ;
typedef  TYPE_2__ KLVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVIO_SEEKABLE_NORMAL ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int FFMIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  IS_KLV_KEY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int avio_rb32 (TYPE_6__*) ; 
 int avio_rb64 (TYPE_6__*) ; 
 int /*<<< orphan*/  avio_seek (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int avio_size (TYPE_6__*) ; 
 int /*<<< orphan*/  avio_skip (TYPE_6__*,int) ; 
 scalar_t__ klv_read_packet (TYPE_2__*,TYPE_6__*) ; 
 int /*<<< orphan*/  mxf_random_index_pack_key ; 

__attribute__((used)) static void mxf_read_random_index_pack(AVFormatContext *s)
{
    MXFContext *mxf = s->priv_data;
    uint32_t length;
    int64_t file_size, max_rip_length, min_rip_length;
    KLVPacket klv;

    if (!(s->pb->seekable & AVIO_SEEKABLE_NORMAL))
        return;

    file_size = avio_size(s->pb);

    /* S377m says to check the RIP length for "silly" values, without defining "silly".
     * The limit below assumes a file with nothing but partition packs and a RIP.
     * Before changing this, consider that a muxer may place each sample in its own partition.
     *
     * 105 is the size of the smallest possible PartitionPack
     * 12 is the size of each RIP entry
     * 28 is the size of the RIP header and footer, assuming an 8-byte BER
     */
    max_rip_length = ((file_size - mxf->run_in) / 105) * 12 + 28;
    max_rip_length = FFMIN(max_rip_length, INT_MAX); //2 GiB and up is also silly

    /* We're only interested in RIPs with at least two entries.. */
    min_rip_length = 16+1+24+4;

    /* See S377m section 11 */
    avio_seek(s->pb, file_size - 4, SEEK_SET);
    length = avio_rb32(s->pb);

    if (length < min_rip_length || length > max_rip_length)
        goto end;
    avio_seek(s->pb, file_size - length, SEEK_SET);
    if (klv_read_packet(&klv, s->pb) < 0 ||
        !IS_KLV_KEY(klv.key, mxf_random_index_pack_key))
        goto end;
    if (klv.next_klv != file_size || klv.length <= 4 || (klv.length - 4) % 12) {
        av_log(s, AV_LOG_WARNING, "Invalid RIP KLV length\n");
        goto end;
    }

    avio_skip(s->pb, klv.length - 12);
    mxf->footer_partition = avio_rb64(s->pb);

    /* sanity check */
    if (mxf->run_in + mxf->footer_partition >= file_size) {
        av_log(s, AV_LOG_WARNING, "bad FooterPartition in RIP - ignoring\n");
        mxf->footer_partition = 0;
    }

end:
    avio_seek(s->pb, mxf->run_in, SEEK_SET);
}