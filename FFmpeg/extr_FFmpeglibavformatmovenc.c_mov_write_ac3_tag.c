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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {int vos_len; scalar_t__ vos_data; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_1__ MOVTrack ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  init_put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mov_write_ac3_tag(AVFormatContext *s, AVIOContext *pb, MOVTrack *track)
{
    GetBitContext gbc;
    PutBitContext pbc;
    uint8_t buf[3];
    int fscod, bsid, bsmod, acmod, lfeon, frmsizecod;

    if (track->vos_len < 7) {
        av_log(s, AV_LOG_ERROR,
               "Cannot write moov atom before AC3 packets."
               " Set the delay_moov flag to fix this.\n");
        return AVERROR(EINVAL);
    }

    avio_wb32(pb, 11);
    ffio_wfourcc(pb, "dac3");

    init_get_bits(&gbc, track->vos_data + 4, (track->vos_len - 4) * 8);
    fscod      = get_bits(&gbc, 2);
    frmsizecod = get_bits(&gbc, 6);
    bsid       = get_bits(&gbc, 5);
    bsmod      = get_bits(&gbc, 3);
    acmod      = get_bits(&gbc, 3);
    if (acmod == 2) {
        skip_bits(&gbc, 2); // dsurmod
    } else {
        if ((acmod & 1) && acmod != 1)
            skip_bits(&gbc, 2); // cmixlev
        if (acmod & 4)
            skip_bits(&gbc, 2); // surmixlev
    }
    lfeon = get_bits1(&gbc);

    init_put_bits(&pbc, buf, sizeof(buf));
    put_bits(&pbc, 2, fscod);
    put_bits(&pbc, 5, bsid);
    put_bits(&pbc, 3, bsmod);
    put_bits(&pbc, 3, acmod);
    put_bits(&pbc, 1, lfeon);
    put_bits(&pbc, 5, frmsizecod >> 1); // bit_rate_code
    put_bits(&pbc, 5, 0); // reserved

    flush_put_bits(&pbc);
    avio_write(pb, buf, sizeof(buf));

    return 11;
}