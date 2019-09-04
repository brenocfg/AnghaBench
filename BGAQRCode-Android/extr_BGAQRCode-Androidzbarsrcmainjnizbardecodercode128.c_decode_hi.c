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
 unsigned char* characters ; 
 int /*<<< orphan*/  dbprintf (int,char*,unsigned char,...) ; 

__attribute__((used)) static inline signed char decode_hi (int sig)
{
    unsigned char rev = (sig & 0x4400) != 0;
    unsigned char idx, c;
    if(rev)
        sig = (((sig >> 12) & 0x000f) |
               ((sig >>  4) & 0x00f0) |
               ((sig <<  4) & 0x0f00) |
               ((sig << 12) & 0xf000));
    dbprintf(2, " rev=%x", rev != 0);

    switch(sig) {
    case 0x0014: idx = 0x0; break;
    case 0x0025: idx = 0x1; break;
    case 0x0034: idx = 0x2; break;
    case 0x0134: idx = 0x3; break;
    case 0x0143: idx = 0x4; break;
    case 0x0243: idx = 0x5; break;
    case 0x0341: idx = 0x6; break;
    case 0x0352: idx = 0x7; break;
    case 0x1024: idx = 0x8; break;
    case 0x1114: idx = 0x9; break;
    case 0x1134: idx = 0xa; break;
    case 0x1242: idx = 0xb; break;
    case 0x1243: idx = 0xc; break;
    case 0x1441: idx = 0xd; rev = 0; break;
    default: return(-1);
    }
    if(rev)
        idx += 0xe;
    c = characters[0x51 + idx];
    dbprintf(2, " %02x => %02x", idx, c);
    return(c);
}