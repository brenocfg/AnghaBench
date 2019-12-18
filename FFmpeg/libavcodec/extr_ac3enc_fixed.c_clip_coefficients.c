#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* vector_clip_int32 ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ;} ;
typedef  TYPE_1__ AudioDSPContext ;

/* Variables and functions */
 int /*<<< orphan*/  COEF_MAX ; 
 int /*<<< orphan*/  COEF_MIN ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void clip_coefficients(AudioDSPContext *adsp, int32_t *coef,
                              unsigned int len)
{
    adsp->vector_clip_int32(coef, coef, COEF_MIN, COEF_MAX, len);
}