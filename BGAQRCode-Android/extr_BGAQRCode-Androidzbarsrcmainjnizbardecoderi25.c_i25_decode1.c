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
 unsigned char decode_e (unsigned int,unsigned int,int) ; 

__attribute__((used)) static inline unsigned char i25_decode1 (unsigned char enc,
                                         unsigned e,
                                         unsigned s)
{
    unsigned char E = decode_e(e, s, 45);
    if(E > 7)
        return(0xff);
    enc <<= 1;
    if(E > 2)
        enc |= 1;
    return(enc);
}