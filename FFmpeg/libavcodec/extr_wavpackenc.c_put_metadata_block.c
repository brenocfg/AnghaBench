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
 int WP_IDF_ODD ; 
 int /*<<< orphan*/  bytestream2_put_byte (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void put_metadata_block(PutByteContext *pb, int flags, int size)
{
    if (size & 1)
        flags |= WP_IDF_ODD;

    bytestream2_put_byte(pb, flags);
    bytestream2_put_byte(pb, (size + 1) >> 1);
}