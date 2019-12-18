#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int int64_t ;
struct TYPE_5__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ MatroskaDemuxContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int INT_MAX ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int* av_malloc (int) ; 
 int* av_malloc_array (int,int) ; 
 int matroska_ebmlnum_sint (TYPE_1__*,int*,int,int*) ; 
 int matroska_ebmlnum_uint (TYPE_1__*,int*,int,int*) ; 

__attribute__((used)) static int matroska_parse_laces(MatroskaDemuxContext *matroska, uint8_t **buf,
                                int *buf_size, int type,
                                uint32_t **lace_buf, int *laces)
{
    int res = 0, n, size = *buf_size;
    uint8_t *data = *buf;
    uint32_t *lace_size;

    if (!type) {
        *laces    = 1;
        *lace_buf = av_malloc(sizeof(**lace_buf));
        if (!*lace_buf)
            return AVERROR(ENOMEM);

        *lace_buf[0] = size;
        return 0;
    }

    av_assert0(size > 0);
    *laces    = *data + 1;
    data     += 1;
    size     -= 1;
    lace_size = av_malloc_array(*laces, sizeof(*lace_size));
    if (!lace_size)
        return AVERROR(ENOMEM);

    switch (type) {
    case 0x1: /* Xiph lacing */
    {
        uint8_t temp;
        uint32_t total = 0;
        for (n = 0; res == 0 && n < *laces - 1; n++) {
            lace_size[n] = 0;

            while (1) {
                if (size <= total) {
                    res = AVERROR_INVALIDDATA;
                    break;
                }
                temp          = *data;
                total        += temp;
                lace_size[n] += temp;
                data         += 1;
                size         -= 1;
                if (temp != 0xff)
                    break;
            }
        }
        if (size <= total) {
            res = AVERROR_INVALIDDATA;
            break;
        }

        lace_size[n] = size - total;
        break;
    }

    case 0x2: /* fixed-size lacing */
        if (size % (*laces)) {
            res = AVERROR_INVALIDDATA;
            break;
        }
        for (n = 0; n < *laces; n++)
            lace_size[n] = size / *laces;
        break;

    case 0x3: /* EBML lacing */
    {
        uint64_t num;
        uint64_t total;
        n = matroska_ebmlnum_uint(matroska, data, size, &num);
        if (n < 0 || num > INT_MAX) {
            av_log(matroska->ctx, AV_LOG_INFO,
                   "EBML block data error\n");
            res = n<0 ? n : AVERROR_INVALIDDATA;
            break;
        }
        data += n;
        size -= n;
        total = lace_size[0] = num;
        for (n = 1; res == 0 && n < *laces - 1; n++) {
            int64_t snum;
            int r;
            r = matroska_ebmlnum_sint(matroska, data, size, &snum);
            if (r < 0 || lace_size[n - 1] + snum > (uint64_t)INT_MAX) {
                av_log(matroska->ctx, AV_LOG_INFO,
                       "EBML block data error\n");
                res = r<0 ? r : AVERROR_INVALIDDATA;
                break;
            }
            data        += r;
            size        -= r;
            lace_size[n] = lace_size[n - 1] + snum;
            total       += lace_size[n];
        }
        if (size <= total) {
            res = AVERROR_INVALIDDATA;
            break;
        }
        lace_size[*laces - 1] = size - total;
        break;
    }
    }

    *buf      = data;
    *lace_buf = lace_size;
    *buf_size = size;

    return res;
}