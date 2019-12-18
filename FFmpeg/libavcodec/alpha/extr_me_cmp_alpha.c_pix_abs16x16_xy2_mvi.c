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
typedef  scalar_t__ uint8_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  avg4 (int,int,int,int) ; 
 int ldq (scalar_t__*) ; 
 scalar_t__ perr (int,int /*<<< orphan*/ ) ; 
 int uldq (scalar_t__*) ; 

__attribute__((used)) static int pix_abs16x16_xy2_mvi(void *v, uint8_t *pix1, uint8_t *pix2, int line_size, int h)
{
    int result = 0;

    uint64_t p1_l, p1_r;
    uint64_t p2_l, p2_r, p2_x;

    p1_l = ldq(pix1);
    p1_r = ldq(pix1 + 8);

    if ((size_t) pix2 & 0x7) { /* could be optimized a lot */
        p2_l = uldq(pix2);
        p2_r = uldq(pix2 + 8);
        p2_x = (uint64_t) pix2[16] << 56;
    } else {
        p2_l = ldq(pix2);
        p2_r = ldq(pix2 + 8);
        p2_x = ldq(pix2 + 16) << 56;
    }

    do {
        uint64_t np1_l, np1_r;
        uint64_t np2_l, np2_r, np2_x;

        pix1 += line_size;
        pix2 += line_size;

        np1_l = ldq(pix1);
        np1_r = ldq(pix1 + 8);

        if ((size_t) pix2 & 0x7) { /* could be optimized a lot */
            np2_l = uldq(pix2);
            np2_r = uldq(pix2 + 8);
            np2_x = (uint64_t) pix2[16] << 56;
        } else {
            np2_l = ldq(pix2);
            np2_r = ldq(pix2 + 8);
            np2_x = ldq(pix2 + 16) << 56;
        }

        result += perr(p1_l,
                       avg4( p2_l, ( p2_l >> 8) | ((uint64_t)  p2_r << 56),
                            np2_l, (np2_l >> 8) | ((uint64_t) np2_r << 56)))
                + perr(p1_r,
                       avg4( p2_r, ( p2_r >> 8) | ((uint64_t)  p2_x),
                            np2_r, (np2_r >> 8) | ((uint64_t) np2_x)));

        p1_l = np1_l;
        p1_r = np1_r;
        p2_l = np2_l;
        p2_r = np2_r;
        p2_x = np2_x;
    } while (--h);

    return result;
}