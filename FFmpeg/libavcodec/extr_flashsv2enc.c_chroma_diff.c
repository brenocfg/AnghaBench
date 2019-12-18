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
 unsigned int ABSDIFF (unsigned int,unsigned int) ; 

__attribute__((used)) static inline unsigned int chroma_diff(unsigned int c1, unsigned int c2)
{
#define ABSDIFF(a,b) (abs((int)(a)-(int)(b)))

    unsigned int t1 = (c1 & 0x000000ff) + ((c1 & 0x0000ff00) >> 8) + ((c1 & 0x00ff0000) >> 16);
    unsigned int t2 = (c2 & 0x000000ff) + ((c2 & 0x0000ff00) >> 8) + ((c2 & 0x00ff0000) >> 16);

    return ABSDIFF(t1, t2) + ABSDIFF(c1 & 0x000000ff, c2 & 0x000000ff) +
        ABSDIFF((c1 & 0x0000ff00) >> 8 , (c2 & 0x0000ff00) >> 8) +
        ABSDIFF((c1 & 0x00ff0000) >> 16, (c2 & 0x00ff0000) >> 16);
}