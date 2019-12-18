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
typedef  int /*<<< orphan*/  PutByteContext ;

/* Variables and functions */
 int /*<<< orphan*/  bytestream2_put_byte (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void put_descr(PutByteContext *pb, int tag, unsigned int size)
{
    int i = 3;
    bytestream2_put_byte(pb, tag);
    for (; i > 0; i--)
        bytestream2_put_byte(pb, (size >> (7 * i)) | 0x80);
    bytestream2_put_byte(pb, size & 0x7F);
}