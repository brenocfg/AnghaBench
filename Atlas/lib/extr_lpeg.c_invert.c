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

__attribute__((used)) static void invert (Instruction *p, int e) {
  int i;
  for (i = 0; i < e; i++, e--) {
    Instruction temp = p[i];
    p[i] = p[e];
    p[e] = temp;
  }
}