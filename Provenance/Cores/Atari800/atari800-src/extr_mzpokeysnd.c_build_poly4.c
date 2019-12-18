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

/* Variables and functions */
 unsigned char* poly4tbl ; 

__attribute__((used)) static void build_poly4(void)
{
    unsigned char c;
    unsigned char i;
    unsigned char poly4=1;

    for(i=0; i<15; i++)
    {
        poly4tbl[i] = ~poly4;
        c = ((poly4>>2)&1) ^ ((poly4>>3)&1);
        poly4 = ((poly4<<1)&15) + c;
    }
}