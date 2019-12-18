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
struct nvt_dev {int /*<<< orphan*/  cr_efir; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFER_EFM_DISABLE ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void nvt_efm_disable(struct nvt_dev *nvt)
{
	outb(EFER_EFM_DISABLE, nvt->cr_efir);
}