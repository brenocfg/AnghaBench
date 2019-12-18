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
 int COSTS_N_INSNS (int) ; 
 int /*<<< orphan*/  SET ; 
 int /*<<< orphan*/  const1_rtx ; 
 int /*<<< orphan*/  gen_rtx_ASHIFT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 int rtx_cost (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  word_mode ; 

__attribute__((used)) static
bool lshift_cheap_p (void)
{
  static bool init = false;
  static bool cheap = true;

  if (!init)
    {
      rtx reg = gen_rtx_REG (word_mode, 10000);
      int cost = rtx_cost (gen_rtx_ASHIFT (word_mode, const1_rtx, reg), SET);
      cheap = cost < COSTS_N_INSNS (3);
      init = true;
    }

  return cheap;
}