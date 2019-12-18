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
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  IS_VP8 ; 
 int vp78_decode_mb_row_sliced (int /*<<< orphan*/ *,void*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vp8_decode_mb_row_sliced(AVCodecContext *avctx, void *tdata,
                                    int jobnr, int threadnr)
{
    return vp78_decode_mb_row_sliced(avctx, tdata, jobnr, threadnr, IS_VP8);
}