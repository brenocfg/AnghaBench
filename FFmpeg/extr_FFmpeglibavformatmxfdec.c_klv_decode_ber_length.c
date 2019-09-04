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
typedef  int uint64_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int INT64_MAX ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int64_t klv_decode_ber_length(AVIOContext *pb)
{
    uint64_t size = avio_r8(pb);
    if (size & 0x80) { /* long form */
        int bytes_num = size & 0x7f;
        /* SMPTE 379M 5.3.4 guarantee that bytes_num must not exceed 8 bytes */
        if (bytes_num > 8)
            return AVERROR_INVALIDDATA;
        size = 0;
        while (bytes_num--)
            size = size << 8 | avio_r8(pb);
    }
    if (size > INT64_MAX)
        return AVERROR_INVALIDDATA;
    return size;
}