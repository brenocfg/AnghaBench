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
typedef  int GXFPktType ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_rb32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parse_packet_header(AVIOContext *pb, GXFPktType *type, int *length) {
    if (avio_rb32(pb))
        return 0;
    if (avio_r8(pb) != 1)
        return 0;
    *type = avio_r8(pb);
    *length = avio_rb32(pb);
    if ((*length >> 24) || *length < 16)
        return 0;
    *length -= 16;
    if (avio_rb32(pb))
        return 0;
    if (avio_r8(pb) != 0xe1)
        return 0;
    if (avio_r8(pb) != 0xe2)
        return 0;
    return 1;
}