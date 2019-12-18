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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_assert (int) ; 
 int s390_branch_condition_mask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
s390_branch_condition_mnemonic (rtx code, int inv)
{
  static const char *const mnemonic[16] =
    {
      NULL, "o", "h", "nle",
      "l", "nhe", "lh", "ne",
      "e", "nlh", "he", "nl",
      "le", "nh", "no", NULL
    };

  int mask = s390_branch_condition_mask (code);
  gcc_assert (mask >= 0);

  if (inv)
    mask ^= 15;

  gcc_assert (mask >= 1 && mask <= 14);

  return mnemonic[mask];
}