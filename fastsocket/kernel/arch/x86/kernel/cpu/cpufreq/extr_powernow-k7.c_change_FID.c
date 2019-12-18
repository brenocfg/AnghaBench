#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int FID; int FIDC; scalar_t__ VIDC; int /*<<< orphan*/  SGTC; } ;
union msr_fidvidctl {int /*<<< orphan*/  val; TYPE_1__ bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_K7_FID_VID_CTL ; 
 int /*<<< orphan*/  latency ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void change_FID(int fid)
{
	union msr_fidvidctl fidvidctl;

	rdmsrl(MSR_K7_FID_VID_CTL, fidvidctl.val);
	if (fidvidctl.bits.FID != fid) {
		fidvidctl.bits.SGTC = latency;
		fidvidctl.bits.FID = fid;
		fidvidctl.bits.VIDC = 0;
		fidvidctl.bits.FIDC = 1;
		wrmsrl(MSR_K7_FID_VID_CTL, fidvidctl.val);
	}
}