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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  MLV_VERSION ; 
 int /*<<< orphan*/  avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 unsigned int avio_rl32 (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_rl64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int check_file_header(AVIOContext *pb, uint64_t guid)
{
    unsigned int size;
    uint8_t version[8];

    avio_skip(pb, 4);
    size = avio_rl32(pb);
    if (size < 52)
        return AVERROR_INVALIDDATA;
    avio_read(pb, version, 8);
    if (memcmp(version, MLV_VERSION, 5) || avio_rl64(pb) != guid)
        return AVERROR_INVALIDDATA;
    avio_skip(pb, size - 24);
    return 0;
}