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
typedef  int /*<<< orphan*/  MatroskaTrack ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int AV_RB32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AV_WB32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int MKBETAG (char,char,char,float) ; 
 int /*<<< orphan*/ * av_malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int matroska_parse_prores(MatroskaTrack *track, uint8_t *src,
                                 uint8_t **pdst, int *size)
{
    uint8_t *dst = src;
    int dstlen = *size;

    if (AV_RB32(&src[4]) != MKBETAG('i', 'c', 'p', 'f')) {
        dstlen += 8;

        dst = av_malloc(dstlen + AV_INPUT_BUFFER_PADDING_SIZE);
        if (!dst)
            return AVERROR(ENOMEM);

        AV_WB32(dst, dstlen);
        AV_WB32(dst + 4, MKBETAG('i', 'c', 'p', 'f'));
        memcpy(dst + 8, src, dstlen - 8);
        memset(dst + dstlen, 0, AV_INPUT_BUFFER_PADDING_SIZE);
    }

    *pdst = dst;
    *size = dstlen;

    return 0;
}