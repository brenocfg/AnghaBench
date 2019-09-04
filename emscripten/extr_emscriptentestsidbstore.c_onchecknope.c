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
 int /*<<< orphan*/  REPORT_RESULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int expected ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  result ; 

void onchecknope(void* arg, int exists)
{
  assert(expected == (int)arg);
  printf("exists (hopefully not)? %d\n", exists);
  assert(!exists);
  REPORT_RESULT(result);
}