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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int avg2 (int,int) ; 
 int extqh (int,int) ; 
 int extql (int,int) ; 
 int ldq (int /*<<< orphan*/ *) ; 
 int ldq_u (int /*<<< orphan*/ *) ; 
 int perr (int,int) ; 

__attribute__((used)) static int pix_abs16x16_x2_mvi(void *v, uint8_t *pix1, uint8_t *pix2, int line_size, int h)
{
    int result = 0;
    uint64_t disalign = (size_t) pix2 & 0x7;

    switch (disalign) {
    case 0:
        do {
            uint64_t p1_l, p1_r, p2_l, p2_r;
            uint64_t l, r;

            p1_l = ldq(pix1);
            p1_r = ldq(pix1 + 8);
            l    = ldq(pix2);
            r    = ldq(pix2 + 8);
            p2_l = avg2(l, (l >> 8) | ((uint64_t) r << 56));
            p2_r = avg2(r, (r >> 8) | ((uint64_t) pix2[16] << 56));
            pix1 += line_size;
            pix2 += line_size;

            result += perr(p1_l, p2_l)
                    + perr(p1_r, p2_r);
        } while (--h);
        break;
    case 7:
        /* |.......l|lllllllr|rrrrrrr*|
           This case is special because disalign1 would be 8, which
           gets treated as 0 by extqh.  At least it is a bit faster
           that way :)  */
        do {
            uint64_t p1_l, p1_r, p2_l, p2_r;
            uint64_t l, m, r;

            p1_l = ldq(pix1);
            p1_r = ldq(pix1 + 8);
            l     = ldq_u(pix2);
            m     = ldq_u(pix2 + 8);
            r     = ldq_u(pix2 + 16);
            p2_l  = avg2(extql(l, disalign) | extqh(m, disalign), m);
            p2_r  = avg2(extql(m, disalign) | extqh(r, disalign), r);
            pix1 += line_size;
            pix2 += line_size;

            result += perr(p1_l, p2_l)
                    + perr(p1_r, p2_r);
        } while (--h);
        break;
    default:
        do {
            uint64_t disalign1 = disalign + 1;
            uint64_t p1_l, p1_r, p2_l, p2_r;
            uint64_t l, m, r;

            p1_l  = ldq(pix1);
            p1_r  = ldq(pix1 + 8);
            l     = ldq_u(pix2);
            m     = ldq_u(pix2 + 8);
            r     = ldq_u(pix2 + 16);
            p2_l  = avg2(extql(l, disalign) | extqh(m, disalign),
                         extql(l, disalign1) | extqh(m, disalign1));
            p2_r  = avg2(extql(m, disalign) | extqh(r, disalign),
                         extql(m, disalign1) | extqh(r, disalign1));
            pix1 += line_size;
            pix2 += line_size;

            result += perr(p1_l, p2_l)
                    + perr(p1_r, p2_r);
        } while (--h);
        break;
    }
    return result;
}