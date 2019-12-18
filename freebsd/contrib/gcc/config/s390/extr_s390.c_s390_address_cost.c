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
struct s390_address {scalar_t__ indx; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int COSTS_N_INSNS (int) ; 
 int /*<<< orphan*/  s390_decompose_address (int /*<<< orphan*/ ,struct s390_address*) ; 

__attribute__((used)) static int
s390_address_cost (rtx addr)
{
  struct s390_address ad;
  if (!s390_decompose_address (addr, &ad))
    return 1000;

  return ad.indx? COSTS_N_INSNS (1) + 1 : COSTS_N_INSNS (1);
}