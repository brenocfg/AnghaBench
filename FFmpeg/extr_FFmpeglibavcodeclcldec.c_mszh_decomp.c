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
 unsigned int FFMIN (unsigned int,int) ; 
 int /*<<< orphan*/  av_memcpy_backptr (unsigned char*,unsigned int,unsigned int) ; 
 unsigned int bytestream_get_le16 (unsigned char const**) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static unsigned int mszh_decomp(const unsigned char * srcptr, int srclen, unsigned char * destptr, unsigned int destsize)
{
    unsigned char *destptr_bak = destptr;
    unsigned char *destptr_end = destptr + destsize;
    const unsigned char *srcptr_end = srcptr + srclen;
    unsigned mask = *srcptr++;
    unsigned maskbit = 0x80;

    while (srcptr < srcptr_end && destptr < destptr_end) {
        if (!(mask & maskbit)) {
            memcpy(destptr, srcptr, 4);
            destptr += 4;
            srcptr += 4;
        } else {
            unsigned ofs = bytestream_get_le16(&srcptr);
            unsigned cnt = (ofs >> 11) + 1;
            ofs &= 0x7ff;
            ofs = FFMIN(ofs, destptr - destptr_bak);
            cnt *= 4;
            cnt = FFMIN(cnt, destptr_end - destptr);
            if (ofs) {
                av_memcpy_backptr(destptr, ofs, cnt);
            } else {
                // Not known what the correct behaviour is, but
                // this at least avoids uninitialized data.
                memset(destptr, 0, cnt);
            }
            destptr += cnt;
        }
        maskbit >>= 1;
        if (!maskbit) {
            mask = *srcptr++;
            while (!mask) {
                if (destptr_end - destptr < 32 || srcptr_end - srcptr < 32) break;
                memcpy(destptr, srcptr, 32);
                destptr += 32;
                srcptr += 32;
                mask = *srcptr++;
            }
            maskbit = 0x80;
        }
    }

    return destptr - destptr_bak;
}