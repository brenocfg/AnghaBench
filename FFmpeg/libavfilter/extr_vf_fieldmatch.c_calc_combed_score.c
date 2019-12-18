#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_10__ {int** data; int* linesize; int width; int height; } ;
struct TYPE_9__ {int cthresh; int** cmask_data; int* cmask_linesize; int blockx; int blocky; int* c_array; int /*<<< orphan*/  vsub; int /*<<< orphan*/  hsub; scalar_t__ chroma; } ;
typedef  TYPE_1__ FieldMatchContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int AV_CEIL_RSHIFT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  C_ARRAY_ADD (int) ; 
 scalar_t__ FILTER (int,int,int,int) ; 
 scalar_t__ HAS_FF_AROUND (int*,int const) ; 
 int /*<<< orphan*/  VERTICAL_HALF (int,int const) ; 
 int abs (int const) ; 
 int /*<<< orphan*/  fill_buf (int*,int const,int const,int const,int) ; 
 int get_height (TYPE_1__ const*,TYPE_2__ const*,int) ; 
 int get_width (TYPE_1__ const*,TYPE_2__ const*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static int calc_combed_score(const FieldMatchContext *fm, const AVFrame *src)
{
    int x, y, plane, max_v = 0;
    const int cthresh = fm->cthresh;
    const int cthresh6 = cthresh * 6;

    for (plane = 0; plane < (fm->chroma ? 3 : 1); plane++) {
        const uint8_t *srcp = src->data[plane];
        const int src_linesize = src->linesize[plane];
        const int width  = get_width (fm, src, plane);
        const int height = get_height(fm, src, plane);
        uint8_t *cmkp = fm->cmask_data[plane];
        const int cmk_linesize = fm->cmask_linesize[plane];

        if (cthresh < 0) {
            fill_buf(cmkp, width, height, cmk_linesize, 0xff);
            continue;
        }
        fill_buf(cmkp, width, height, cmk_linesize, 0);

        /* [1 -3 4 -3 1] vertical filter */
#define FILTER(xm2, xm1, xp1, xp2) \
        abs(  4 * srcp[x] \
             -3 * (srcp[x + (xm1)*src_linesize] + srcp[x + (xp1)*src_linesize]) \
             +    (srcp[x + (xm2)*src_linesize] + srcp[x + (xp2)*src_linesize])) > cthresh6

        /* first line */
        for (x = 0; x < width; x++) {
            const int s1 = abs(srcp[x] - srcp[x + src_linesize]);
            if (s1 > cthresh && FILTER(2, 1, 1, 2))
                cmkp[x] = 0xff;
        }
        srcp += src_linesize;
        cmkp += cmk_linesize;

        /* second line */
        for (x = 0; x < width; x++) {
            const int s1 = abs(srcp[x] - srcp[x - src_linesize]);
            const int s2 = abs(srcp[x] - srcp[x + src_linesize]);
            if (s1 > cthresh && s2 > cthresh && FILTER(2, -1, 1, 2))
                cmkp[x] = 0xff;
        }
        srcp += src_linesize;
        cmkp += cmk_linesize;

        /* all lines minus first two and last two */
        for (y = 2; y < height-2; y++) {
            for (x = 0; x < width; x++) {
                const int s1 = abs(srcp[x] - srcp[x - src_linesize]);
                const int s2 = abs(srcp[x] - srcp[x + src_linesize]);
                if (s1 > cthresh && s2 > cthresh && FILTER(-2, -1, 1, 2))
                    cmkp[x] = 0xff;
            }
            srcp += src_linesize;
            cmkp += cmk_linesize;
        }

        /* before-last line */
        for (x = 0; x < width; x++) {
            const int s1 = abs(srcp[x] - srcp[x - src_linesize]);
            const int s2 = abs(srcp[x] - srcp[x + src_linesize]);
            if (s1 > cthresh && s2 > cthresh && FILTER(-2, -1, 1, -2))
                cmkp[x] = 0xff;
        }
        srcp += src_linesize;
        cmkp += cmk_linesize;

        /* last line */
        for (x = 0; x < width; x++) {
            const int s1 = abs(srcp[x] - srcp[x - src_linesize]);
            if (s1 > cthresh && FILTER(-2, -1, -1, -2))
                cmkp[x] = 0xff;
        }
    }

    if (fm->chroma) {
        uint8_t *cmkp  = fm->cmask_data[0];
        uint8_t *cmkpU = fm->cmask_data[1];
        uint8_t *cmkpV = fm->cmask_data[2];
        const int width  = AV_CEIL_RSHIFT(src->width,  fm->hsub);
        const int height = AV_CEIL_RSHIFT(src->height, fm->vsub);
        const int cmk_linesize   = fm->cmask_linesize[0] << 1;
        const int cmk_linesizeUV = fm->cmask_linesize[2];
        uint8_t *cmkpp  = cmkp - (cmk_linesize>>1);
        uint8_t *cmkpn  = cmkp + (cmk_linesize>>1);
        uint8_t *cmkpnn = cmkp +  cmk_linesize;
        for (y = 1; y < height - 1; y++) {
            cmkpp  += cmk_linesize;
            cmkp   += cmk_linesize;
            cmkpn  += cmk_linesize;
            cmkpnn += cmk_linesize;
            cmkpV  += cmk_linesizeUV;
            cmkpU  += cmk_linesizeUV;
            for (x = 1; x < width - 1; x++) {
#define HAS_FF_AROUND(p, lz) (p[(x)-1 - (lz)] == 0xff || p[(x) - (lz)] == 0xff || p[(x)+1 - (lz)] == 0xff || \
                              p[(x)-1       ] == 0xff ||                          p[(x)+1       ] == 0xff || \
                              p[(x)-1 + (lz)] == 0xff || p[(x) + (lz)] == 0xff || p[(x)+1 + (lz)] == 0xff)
                if ((cmkpV[x] == 0xff && HAS_FF_AROUND(cmkpV, cmk_linesizeUV)) ||
                    (cmkpU[x] == 0xff && HAS_FF_AROUND(cmkpU, cmk_linesizeUV))) {
                    ((uint16_t*)cmkp)[x]  = 0xffff;
                    ((uint16_t*)cmkpn)[x] = 0xffff;
                    if (y&1) ((uint16_t*)cmkpp)[x]  = 0xffff;
                    else     ((uint16_t*)cmkpnn)[x] = 0xffff;
                }
            }
        }
    }

    {
        const int blockx = fm->blockx;
        const int blocky = fm->blocky;
        const int xhalf = blockx/2;
        const int yhalf = blocky/2;
        const int cmk_linesize = fm->cmask_linesize[0];
        const uint8_t *cmkp    = fm->cmask_data[0] + cmk_linesize;
        const int width  = src->width;
        const int height = src->height;
        const int xblocks = ((width+xhalf)/blockx) + 1;
        const int xblocks4 = xblocks<<2;
        const int yblocks = ((height+yhalf)/blocky) + 1;
        int *c_array = fm->c_array;
        const int arraysize = (xblocks*yblocks)<<2;
        int      heighta = (height/(blocky/2))*(blocky/2);
        const int widtha = (width /(blockx/2))*(blockx/2);
        if (heighta == height)
            heighta = height - yhalf;
        memset(c_array, 0, arraysize * sizeof(*c_array));

#define C_ARRAY_ADD(v) do {                         \
    const int box1 = (x / blockx) * 4;              \
    const int box2 = ((x + xhalf) / blockx) * 4;    \
    c_array[temp1 + box1    ] += v;                 \
    c_array[temp1 + box2 + 1] += v;                 \
    c_array[temp2 + box1 + 2] += v;                 \
    c_array[temp2 + box2 + 3] += v;                 \
} while (0)

#define VERTICAL_HALF(y_start, y_end) do {                                  \
    for (y = y_start; y < y_end; y++) {                                     \
        const int temp1 = (y / blocky) * xblocks4;                          \
        const int temp2 = ((y + yhalf) / blocky) * xblocks4;                \
        for (x = 0; x < width; x++)                                         \
            if (cmkp[x - cmk_linesize] == 0xff &&                           \
                cmkp[x               ] == 0xff &&                           \
                cmkp[x + cmk_linesize] == 0xff)                             \
                C_ARRAY_ADD(1);                                             \
        cmkp += cmk_linesize;                                               \
    }                                                                       \
} while (0)

        VERTICAL_HALF(1, yhalf);

        for (y = yhalf; y < heighta; y += yhalf) {
            const int temp1 = (y / blocky) * xblocks4;
            const int temp2 = ((y + yhalf) / blocky) * xblocks4;

            for (x = 0; x < widtha; x += xhalf) {
                const uint8_t *cmkp_tmp = cmkp + x;
                int u, v, sum = 0;
                for (u = 0; u < yhalf; u++) {
                    for (v = 0; v < xhalf; v++)
                        if (cmkp_tmp[v - cmk_linesize] == 0xff &&
                            cmkp_tmp[v               ] == 0xff &&
                            cmkp_tmp[v + cmk_linesize] == 0xff)
                            sum++;
                    cmkp_tmp += cmk_linesize;
                }
                if (sum)
                    C_ARRAY_ADD(sum);
            }

            for (x = widtha; x < width; x++) {
                const uint8_t *cmkp_tmp = cmkp + x;
                int u, sum = 0;
                for (u = 0; u < yhalf; u++) {
                    if (cmkp_tmp[-cmk_linesize] == 0xff &&
                        cmkp_tmp[            0] == 0xff &&
                        cmkp_tmp[ cmk_linesize] == 0xff)
                        sum++;
                    cmkp_tmp += cmk_linesize;
                }
                if (sum)
                    C_ARRAY_ADD(sum);
            }

            cmkp += cmk_linesize * yhalf;
        }

        VERTICAL_HALF(heighta, height - 1);

        for (x = 0; x < arraysize; x++)
            if (c_array[x] > max_v)
                max_v = c_array[x];
    }
    return max_v;
}