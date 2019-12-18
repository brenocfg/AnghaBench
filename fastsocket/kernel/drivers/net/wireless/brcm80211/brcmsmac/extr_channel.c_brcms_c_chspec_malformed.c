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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS20 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHSPEC_IS40 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHSPEC_IS5G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHSPEC_SB_LOWER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHSPEC_SB_NONE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHSPEC_SB_UPPER (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool brcms_c_chspec_malformed(u16 chanspec)
{
	/* must be 2G or 5G band */
	if (!CHSPEC_IS5G(chanspec) && !CHSPEC_IS2G(chanspec))
		return true;
	/* must be 20 or 40 bandwidth */
	if (!CHSPEC_IS40(chanspec) && !CHSPEC_IS20(chanspec))
		return true;

	/* 20MHZ b/w must have no ctl sb, 40 must have a ctl sb */
	if (CHSPEC_IS20(chanspec)) {
		if (!CHSPEC_SB_NONE(chanspec))
			return true;
	} else if (!CHSPEC_SB_UPPER(chanspec) && !CHSPEC_SB_LOWER(chanspec)) {
		return true;
	}

	return false;
}