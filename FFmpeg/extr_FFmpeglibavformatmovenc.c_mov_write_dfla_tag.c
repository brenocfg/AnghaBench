#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {TYPE_1__* par; } ;
struct TYPE_4__ {scalar_t__ extradata_size; int /*<<< orphan*/  extradata; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int FLAC_METADATA_TYPE_STREAMINFO ; 
 scalar_t__ FLAC_STREAMINFO_SIZE ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb24 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int update_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mov_write_dfla_tag(AVIOContext *pb, MOVTrack *track)
{
    int64_t pos = avio_tell(pb);
    avio_wb32(pb, 0);
    ffio_wfourcc(pb, "dfLa");
    avio_w8(pb, 0); /* version */
    avio_wb24(pb, 0); /* flags */

    /* Expect the encoder to pass a METADATA_BLOCK_TYPE_STREAMINFO. */
    if (track->par->extradata_size != FLAC_STREAMINFO_SIZE)
        return AVERROR_INVALIDDATA;

    /* TODO: Write other METADATA_BLOCK_TYPEs if the encoder makes them available. */
    avio_w8(pb, 1 << 7 | FLAC_METADATA_TYPE_STREAMINFO); /* LastMetadataBlockFlag << 7 | BlockType */
    avio_wb24(pb, track->par->extradata_size); /* Length */
    avio_write(pb, track->par->extradata, track->par->extradata_size); /* BlockData[Length] */

    return update_size(pb, pos);
}