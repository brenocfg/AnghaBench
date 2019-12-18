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

/* Variables and functions */
 int /*<<< orphan*/  _dos_ds ; 
 unsigned long _farpeekl (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pdbr ; 

__attribute__((used)) static unsigned long
get_pde (int n)
{
  unsigned long pde = 0;

  if (pdbr && n >= 0 && n < 1024)
    {
      pde = _farpeekl (_dos_ds, pdbr + 4*n);
    }
  return pde;
}