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
 int /*<<< orphan*/  multi_vararg (int,int,int,int,int,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int,int,int) ; 

int main() {
  multi_vararg(5,
               8, 6, 4, 2, 0,
               1, 3, 5, 7, 9,
               4, 5, 6, 7, 8
               );
  return 0;
}