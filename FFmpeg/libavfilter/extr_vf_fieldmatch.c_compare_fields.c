#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
struct TYPE_12__ {int** data; int* linesize; } ;
struct TYPE_11__ {int** map_data; int* map_linesize; int y0; int vsub; int y1; int hsub; scalar_t__ mchroma; TYPE_2__* src; } ;
typedef  TYPE_1__ FieldMatchContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int FFMAX (int,int) ; 
 int FFMIN (int,int) ; 
 int abs (int) ; 
 int /*<<< orphan*/  build_diff_map (TYPE_1__*,int const*,int,int const*,int,int*,int,int const,int const,int) ; 
 int /*<<< orphan*/  fill_buf (int*,int const,int const,int,int /*<<< orphan*/ ) ; 
 int get_field_base (int,int) ; 
 int get_height (TYPE_1__*,TYPE_2__ const*,int) ; 
 int get_width (TYPE_1__*,TYPE_2__ const*,int) ; 
 TYPE_2__* select_frame (TYPE_1__*,int) ; 

__attribute__((used)) static int compare_fields(FieldMatchContext *fm, int match1, int match2, int field)
{
    int plane, ret;
    uint64_t accumPc = 0, accumPm = 0, accumPml = 0;
    uint64_t accumNc = 0, accumNm = 0, accumNml = 0;
    int norm1, norm2, mtn1, mtn2;
    float c1, c2, mr;
    const AVFrame *src = fm->src;

    for (plane = 0; plane < (fm->mchroma ? 3 : 1); plane++) {
        int x, y, temp1, temp2, fbase;
        const AVFrame *prev, *next;
        uint8_t *mapp    = fm->map_data[plane];
        int map_linesize = fm->map_linesize[plane];
        const uint8_t *srcp = src->data[plane];
        const int src_linesize  = src->linesize[plane];
        const int srcf_linesize = src_linesize << 1;
        int prv_linesize,  nxt_linesize;
        int prvf_linesize, nxtf_linesize;
        const int width  = get_width (fm, src, plane);
        const int height = get_height(fm, src, plane);
        const int y0a = fm->y0 >> (plane ? fm->vsub : 0);
        const int y1a = fm->y1 >> (plane ? fm->vsub : 0);
        const int startx = (plane == 0 ? 8 : 8 >> fm->hsub);
        const int stopx  = width - startx;
        const uint8_t *srcpf, *srcf, *srcnf;
        const uint8_t *prvpf, *prvnf, *nxtpf, *nxtnf;

        fill_buf(mapp, width, height, map_linesize, 0);

        /* match1 */
        fbase = get_field_base(match1, field);
        srcf  = srcp + (fbase + 1) * src_linesize;
        srcpf = srcf - srcf_linesize;
        srcnf = srcf + srcf_linesize;
        mapp  = mapp + fbase * map_linesize;
        prev = select_frame(fm, match1);
        prv_linesize  = prev->linesize[plane];
        prvf_linesize = prv_linesize << 1;
        prvpf = prev->data[plane] + fbase * prv_linesize;   // previous frame, previous field
        prvnf = prvpf + prvf_linesize;                      // previous frame, next     field

        /* match2 */
        fbase = get_field_base(match2, field);
        next = select_frame(fm, match2);
        nxt_linesize  = next->linesize[plane];
        nxtf_linesize = nxt_linesize << 1;
        nxtpf = next->data[plane] + fbase * nxt_linesize;   // next frame, previous field
        nxtnf = nxtpf + nxtf_linesize;                      // next frame, next     field

        map_linesize <<= 1;
        if ((match1 >= 3 && field == 1) || (match1 < 3 && field != 1))
            build_diff_map(fm, prvpf, prvf_linesize, nxtpf, nxtf_linesize,
                           mapp, map_linesize, height, width, plane);
        else
            build_diff_map(fm, prvnf, prvf_linesize, nxtnf, nxtf_linesize,
                           mapp + map_linesize, map_linesize, height, width, plane);

        for (y = 2; y < height - 2; y += 2) {
            if (y0a == y1a || y < y0a || y > y1a) {
                for (x = startx; x < stopx; x++) {
                    if (mapp[x] > 0 || mapp[x + map_linesize] > 0) {
                        temp1 = srcpf[x] + (srcf[x] << 2) + srcnf[x]; // [1 4 1]

                        temp2 = abs(3 * (prvpf[x] + prvnf[x]) - temp1);
                        if (temp2 > 23 && ((mapp[x]&1) || (mapp[x + map_linesize]&1)))
                            accumPc += temp2;
                        if (temp2 > 42) {
                            if ((mapp[x]&2) || (mapp[x + map_linesize]&2))
                                accumPm += temp2;
                            if ((mapp[x]&4) || (mapp[x + map_linesize]&4))
                                accumPml += temp2;
                        }

                        temp2 = abs(3 * (nxtpf[x] + nxtnf[x]) - temp1);
                        if (temp2 > 23 && ((mapp[x]&1) || (mapp[x + map_linesize]&1)))
                            accumNc += temp2;
                        if (temp2 > 42) {
                            if ((mapp[x]&2) || (mapp[x + map_linesize]&2))
                                accumNm += temp2;
                            if ((mapp[x]&4) || (mapp[x + map_linesize]&4))
                                accumNml += temp2;
                        }
                    }
                }
            }
            prvpf += prvf_linesize;
            prvnf += prvf_linesize;
            srcpf += srcf_linesize;
            srcf  += srcf_linesize;
            srcnf += srcf_linesize;
            nxtpf += nxtf_linesize;
            nxtnf += nxtf_linesize;
            mapp  += map_linesize;
        }
    }

    if (accumPm < 500 && accumNm < 500 && (accumPml >= 500 || accumNml >= 500) &&
        FFMAX(accumPml,accumNml) > 3*FFMIN(accumPml,accumNml)) {
        accumPm = accumPml;
        accumNm = accumNml;
    }

    norm1 = (int)((accumPc / 6.0f) + 0.5f);
    norm2 = (int)((accumNc / 6.0f) + 0.5f);
    mtn1  = (int)((accumPm / 6.0f) + 0.5f);
    mtn2  = (int)((accumNm / 6.0f) + 0.5f);
    c1 = ((float)FFMAX(norm1,norm2)) / ((float)FFMAX(FFMIN(norm1,norm2),1));
    c2 = ((float)FFMAX(mtn1, mtn2))  / ((float)FFMAX(FFMIN(mtn1, mtn2), 1));
    mr = ((float)FFMAX(mtn1, mtn2))  / ((float)FFMAX(FFMAX(norm1,norm2),1));
    if (((mtn1 >=  500 || mtn2 >=  500) && (mtn1*2 < mtn2*1 || mtn2*2 < mtn1*1)) ||
        ((mtn1 >= 1000 || mtn2 >= 1000) && (mtn1*3 < mtn2*2 || mtn2*3 < mtn1*2)) ||
        ((mtn1 >= 2000 || mtn2 >= 2000) && (mtn1*5 < mtn2*4 || mtn2*5 < mtn1*4)) ||
        ((mtn1 >= 4000 || mtn2 >= 4000) && c2 > c1))
        ret = mtn1 > mtn2 ? match2 : match1;
    else if (mr > 0.005 && FFMAX(mtn1, mtn2) > 150 && (mtn1*2 < mtn2*1 || mtn2*2 < mtn1*1))
        ret = mtn1 > mtn2 ? match2 : match1;
    else
        ret = norm1 > norm2 ? match2 : match1;
    return ret;
}