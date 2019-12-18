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
typedef  enum TwinVQFrameType { ____Placeholder_TwinVQFrameType } TwinVQFrameType ;
typedef  int /*<<< orphan*/  TwinVQContext ;

/* Variables and functions */
 int /*<<< orphan*/  eval_lpcenv_or_interp (int /*<<< orphan*/ *,int,float*,float const*,int,int,int) ; 
 int /*<<< orphan*/  interpolate (float*,float,float,int) ; 
 int /*<<< orphan*/  twinvq_memset_float (float*,float,int) ; 

__attribute__((used)) static void eval_lpcenv_2parts(TwinVQContext *tctx, enum TwinVQFrameType ftype,
                               const float *buf, float *lpc,
                               int size, int step)
{
    eval_lpcenv_or_interp(tctx, ftype, lpc, buf, size / 2, step, 0);
    eval_lpcenv_or_interp(tctx, ftype, lpc + size / 2, buf, size / 2,
                          2 * step, 1);

    interpolate(lpc + size / 2 - step + 1, lpc[size / 2],
                lpc[size / 2 - step], step);

    twinvq_memset_float(lpc + size - 2 * step + 1, lpc[size - 2 * step],
                        2 * step - 1);
}