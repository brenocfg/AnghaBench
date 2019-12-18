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
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gxf_write_packet_header(AVIOContext *pb, GXFPktType type)
{
    avio_wb32(pb, 0);  /* packet leader for synchro */
    avio_w8(pb, 1);
    avio_w8(pb, type); /* map packet */
    avio_wb32(pb, 0);  /* size */
    avio_wb32(pb, 0);  /* reserved */
    avio_w8(pb, 0xE1); /* trailer 1 */
    avio_w8(pb, 0xE2); /* trailer 2 */
}