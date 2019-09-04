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
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void put_descr(AVIOContext *pb, int tag, unsigned int size)
{
    int i = 3;
    avio_w8(pb, tag);
    for (; i > 0; i--)
        avio_w8(pb, (size >> (7 * i)) | 0x80);
    avio_w8(pb, size & 0x7F);
}