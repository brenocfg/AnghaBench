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
typedef  int u16 ;

/* Variables and functions */
 int be32_to_cpu (unsigned int) ; 

__attribute__((used)) static u16 csr_crc16(unsigned *data, int length)
{
        int check=0, i;
        int shift, sum, next=0;

        for (i = length; i; i--) {
                for (next = check, shift = 28; shift >= 0; shift -= 4 ) {
                        sum = ((next >> 12) ^ (be32_to_cpu(*data) >> shift)) & 0xf;
                        next = (next << 4) ^ (sum << 12) ^ (sum << 5) ^ (sum);
                }
                check = next & 0xffff;
                data++;
        }

        return check;
}