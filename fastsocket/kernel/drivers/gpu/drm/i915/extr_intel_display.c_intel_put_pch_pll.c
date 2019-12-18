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
struct intel_pch_pll {scalar_t__ refcount; } ;
struct intel_crtc {struct intel_pch_pll* pch_pll; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 

__attribute__((used)) static void intel_put_pch_pll(struct intel_crtc *intel_crtc)
{
	struct intel_pch_pll *pll = intel_crtc->pch_pll;

	if (pll == NULL)
		return;

	if (pll->refcount == 0) {
		WARN(1, "bad PCH PLL refcount\n");
		return;
	}

	--pll->refcount;
	intel_crtc->pch_pll = NULL;
}