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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* fdct ) (int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ FDCTDSPContext ;

/* Variables and functions */
 int /*<<< orphan*/  get (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fdct_get(FDCTDSPContext *fdsp, uint8_t *pixels, int stride, int16_t* block)
{
    get(pixels, stride, block);
    fdsp->fdct(block);
}