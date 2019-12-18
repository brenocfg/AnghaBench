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
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_pad (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int write_table0_header_events(AVIOContext *pb)
{
    avio_wl32(pb, 0x10);
    write_pad(pb, 84);
    avio_wl64(pb, 0x32);
    return 96;
}