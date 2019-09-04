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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_read (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  ff_parse_pes_pts (int*) ; 

__attribute__((used)) static int64_t get_pts(AVIOContext *pb, int c)
{
    uint8_t buf[5];

    buf[0] = c < 0 ? avio_r8(pb) : c;
    avio_read(pb, buf + 1, 4);

    return ff_parse_pes_pts(buf);
}