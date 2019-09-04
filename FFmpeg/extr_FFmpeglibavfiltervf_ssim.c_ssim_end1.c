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

/* Variables and functions */

__attribute__((used)) static float ssim_end1(int s1, int s2, int ss, int s12)
{
    static const int ssim_c1 = (int)(.01*.01*255*255*64 + .5);
    static const int ssim_c2 = (int)(.03*.03*255*255*64*63 + .5);

    int fs1 = s1;
    int fs2 = s2;
    int fss = ss;
    int fs12 = s12;
    int vars = fss * 64 - fs1 * fs1 - fs2 * fs2;
    int covar = fs12 * 64 - fs1 * fs2;

    return (float)(2 * fs1 * fs2 + ssim_c1) * (float)(2 * covar + ssim_c2)
         / ((float)(fs1 * fs1 + fs2 * fs2 + ssim_c1) * (float)(vars + ssim_c2));
}