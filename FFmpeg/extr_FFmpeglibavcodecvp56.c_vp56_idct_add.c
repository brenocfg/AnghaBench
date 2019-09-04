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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* idct_dc_add ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* idct_add ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {TYPE_1__ vp3dsp; } ;
typedef  TYPE_2__ VP56Context ;

/* Variables and functions */
 int /*<<< orphan*/  ff_vp3dsp_idct10_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vp56_idct_add(VP56Context *s, uint8_t * dest, ptrdiff_t stride, int16_t *block, int selector)
{
    if (selector > 10)
        s->vp3dsp.idct_add(dest, stride, block);
    else if (selector > 1)
        ff_vp3dsp_idct10_add(dest, stride, block);
    else
        s->vp3dsp.idct_dc_add(dest, stride, block);
}