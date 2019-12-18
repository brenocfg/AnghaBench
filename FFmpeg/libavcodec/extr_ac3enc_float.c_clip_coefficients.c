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
struct TYPE_3__ {int /*<<< orphan*/  (* vector_clipf ) (float*,float*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ AudioDSPContext ;

/* Variables and functions */
 int /*<<< orphan*/  COEF_MAX ; 
 int /*<<< orphan*/  COEF_MIN ; 
 int /*<<< orphan*/  stub1 (float*,float*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clip_coefficients(AudioDSPContext *adsp, float *coef,
                              unsigned int len)
{
    adsp->vector_clipf(coef, coef, len, COEF_MIN, COEF_MAX);
}