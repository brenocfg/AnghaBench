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
 int /*<<< orphan*/  invert (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void rotate (Instruction *p, int e, int n) {
  invert(p, n - 1);
  invert(p + n, e - n);
  invert(p, e);
}