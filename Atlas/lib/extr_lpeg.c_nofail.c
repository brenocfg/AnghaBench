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
typedef  int /*<<< orphan*/  Instruction ;

/* Variables and functions */
 int /*<<< orphan*/  isnofail (int /*<<< orphan*/ *) ; 
 scalar_t__ sizei (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nofail (Instruction *p, int l) {
  int i;
  for (i = 0; i < l; i += sizei(p + i)) {
    if (!isnofail(p + i)) return 0;
  }
  return 1;
}