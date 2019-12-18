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
typedef  int /*<<< orphan*/  HuffYUVDSPContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PIX_FMT_YUV422P ; 
 int av_clip (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  check_add_int16 (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  ff_huffyuvdsp_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report (char*) ; 
 int /*<<< orphan*/  rnd () ; 

void checkasm_check_huffyuvdsp(void)
{
    HuffYUVDSPContext c;
    int width = 16 * av_clip(rnd(), 16, 128);

    ff_huffyuvdsp_init(&c, AV_PIX_FMT_YUV422P);

    /*! test width not multiple of mmsize */
    check_add_int16(c, 65535, width, "add_int16_rnd_width");
    report("add_int16_rnd_width");

    /*! test always with the same size (for perf test) */
    check_add_int16(c, 65535, 16*128, "add_int16_128");
    report("add_int16_128");
}