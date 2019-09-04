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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int avio_r8 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t read_arbitrary(AVIOContext *pb)
{
    uint8_t size, byte;
    int i;
    uint32_t word;

    size = avio_r8(pb);

    word = 0;
    for (i = 0; i < size; i++) {
        byte   = avio_r8(pb);
        word <<= 8;
        word  |= byte;
    }

    return word;
}