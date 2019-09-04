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
typedef  int /*<<< orphan*/  kissf_fft_cpx ;
typedef  int /*<<< orphan*/  kissf_fft_cfg ;

/* Variables and functions */
 int /*<<< orphan*/  kissf_fft_stride (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 

void kissf_fft(kissf_fft_cfg cfg,const kissf_fft_cpx *fin,kissf_fft_cpx *fout)
{
    kissf_fft_stride(cfg,fin,fout,1);
}