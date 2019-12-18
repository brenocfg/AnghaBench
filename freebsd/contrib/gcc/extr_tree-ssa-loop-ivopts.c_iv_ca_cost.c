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
struct iv_ca {int cost; scalar_t__ bad_uses; } ;

/* Variables and functions */
 int INFTY ; 

__attribute__((used)) static unsigned
iv_ca_cost (struct iv_ca *ivs)
{
  return (ivs->bad_uses ? INFTY : ivs->cost);
}