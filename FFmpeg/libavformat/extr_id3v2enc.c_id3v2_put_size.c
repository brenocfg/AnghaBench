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
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void id3v2_put_size(AVIOContext *pb, int size)
{
    avio_w8(pb, size >> 21 & 0x7f);
    avio_w8(pb, size >> 14 & 0x7f);
    avio_w8(pb, size >> 7  & 0x7f);
    avio_w8(pb, size       & 0x7f);
}