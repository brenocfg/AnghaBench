#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  ff_asf_guid ;

/* Variables and functions */
 scalar_t__ AV_RL32 (int /*<<< orphan*/ *) ; 
 int AV_RL64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AV_WL32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_asf_file_header ; 
 int /*<<< orphan*/  ff_asf_header ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rtp_asf_fix_header(uint8_t *buf, int len)
{
    uint8_t *p = buf, *end = buf + len;

    if (len < sizeof(ff_asf_guid) * 2 + 22 ||
        memcmp(p, ff_asf_header, sizeof(ff_asf_guid))) {
        return -1;
    }
    p += sizeof(ff_asf_guid) + 14;
    do {
        uint64_t chunksize = AV_RL64(p + sizeof(ff_asf_guid));
        int skip = 6 * 8 + 3 * 4 + sizeof(ff_asf_guid) * 2;
        if (memcmp(p, ff_asf_file_header, sizeof(ff_asf_guid))) {
            if (chunksize > end - p)
                return -1;
            p += chunksize;
            continue;
        }

        if (end - p < 8 + skip)
            break;
        /* skip most of the file header, to min_pktsize */
        p += skip;
        if (AV_RL32(p) == AV_RL32(p + 4)) {
            /* and set that to zero */
            AV_WL32(p, 0);
            return 0;
        }
        break;
    } while (end - p >= sizeof(ff_asf_guid) + 8);

    return -1;
}