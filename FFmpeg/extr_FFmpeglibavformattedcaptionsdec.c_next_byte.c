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
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int avio_read (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static void next_byte(AVIOContext *pb, int *cur_byte)
{
    uint8_t b;
    int ret = avio_read(pb, &b, 1);
    *cur_byte = ret > 0 ? b : ret == 0 ? AVERROR_EOF : ret;
}