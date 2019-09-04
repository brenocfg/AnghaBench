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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  PKT_EOS ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gxf_write_packet_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int updatePacketSize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gxf_write_eos_packet(AVIOContext *pb)
{
    int64_t pos = avio_tell(pb);

    gxf_write_packet_header(pb, PKT_EOS);
    return updatePacketSize(pb, pos);
}