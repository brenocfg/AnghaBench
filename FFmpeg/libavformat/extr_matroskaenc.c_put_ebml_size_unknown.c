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
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_fill (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void put_ebml_size_unknown(AVIOContext *pb, int bytes)
{
    av_assert0(bytes <= 8);
    avio_w8(pb, 0x1ff >> bytes);
    ffio_fill(pb, 0xff, bytes - 1);
}