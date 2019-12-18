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
typedef  int int64_t ;

/* Variables and functions */

__attribute__((used)) static float ssim_end1x(int64_t s1, int64_t s2, int64_t ss, int64_t s12, int max)
{
    int64_t ssim_c1 = (int64_t)(.01*.01*max*max*64 + .5);
    int64_t ssim_c2 = (int64_t)(.03*.03*max*max*64*63 + .5);

    int64_t fs1 = s1;
    int64_t fs2 = s2;
    int64_t fss = ss;
    int64_t fs12 = s12;
    int64_t vars = fss * 64 - fs1 * fs1 - fs2 * fs2;
    int64_t covar = fs12 * 64 - fs1 * fs2;

    return (float)(2 * fs1 * fs2 + ssim_c1) * (float)(2 * covar + ssim_c2)
         / ((float)(fs1 * fs1 + fs2 * fs2 + ssim_c1) * (float)(vars + ssim_c2));
}