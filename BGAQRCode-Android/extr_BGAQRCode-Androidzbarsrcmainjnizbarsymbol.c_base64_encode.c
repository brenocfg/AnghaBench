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

unsigned base64_encode (char *dst,
                        const char *src,
                        unsigned srclen)
{
    static const char alphabet[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    char *start = dst;
    int nline = 19;
    for(; srclen; srclen -= 3) {
        unsigned int buf = *(src++) << 16;
        if(srclen > 1) buf |= *(src++) << 8;
        if(srclen > 2) buf |= *(src++);
        *(dst++) = alphabet[(buf >> 18) & 0x3f];
        *(dst++) = alphabet[(buf >> 12) & 0x3f];
        *(dst++) = (srclen > 1) ? alphabet[(buf >> 6) & 0x3f] : '=';
        *(dst++) = (srclen > 2) ? alphabet[buf & 0x3f] : '=';
        if(srclen < 3) break;
        if(!--nline) { *(dst++) = '\n'; nline = 19; }
    }
    *(dst++) = '\n';
    *(dst++) = '\0';
    return(dst - start - 1);
}