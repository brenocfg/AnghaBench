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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int EINVAL ; 
 int SAD_PKG0 (int /*<<< orphan*/ ) ; 
 int SAD_PKG1 (int /*<<< orphan*/ ) ; 
 int SAD_PKG2 (int /*<<< orphan*/ ) ; 
 int SAD_PKG3 (int /*<<< orphan*/ ) ; 
 int SAD_PKG4 (int /*<<< orphan*/ ) ; 
 int SAD_PKG5 (int /*<<< orphan*/ ) ; 
 int SAD_PKG6 (int /*<<< orphan*/ ) ; 
 int SAD_PKG7 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int sad_pkg(u32 reg, int interleave)
{
	switch (interleave) {
	case 0:
		return SAD_PKG0(reg);
	case 1:
		return SAD_PKG1(reg);
	case 2:
		return SAD_PKG2(reg);
	case 3:
		return SAD_PKG3(reg);
	case 4:
		return SAD_PKG4(reg);
	case 5:
		return SAD_PKG5(reg);
	case 6:
		return SAD_PKG6(reg);
	case 7:
		return SAD_PKG7(reg);
	default:
		return -EINVAL;
	}
}