#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* sum_square_butterfly_int32 ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ;} ;
struct TYPE_5__ {TYPE_1__ ac3dsp; } ;
typedef  TYPE_2__ AC3EncodeContext ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void sum_square_butterfly(AC3EncodeContext *s, int64_t sum[4],
                                 const int32_t *coef0, const int32_t *coef1,
                                 int len)
{
    s->ac3dsp.sum_square_butterfly_int32(sum, coef0, coef1, len);
}