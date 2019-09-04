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
 int /*<<< orphan*/  avio_wb24 (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  ffio_fill (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int flac_write_block_padding(AVIOContext *pb, unsigned int n_padding_bytes,
                                    int last_block)
{
    avio_w8(pb, last_block ? 0x81 : 0x01);
    avio_wb24(pb, n_padding_bytes);
    ffio_fill(pb, 0, n_padding_bytes);
    return 0;
}