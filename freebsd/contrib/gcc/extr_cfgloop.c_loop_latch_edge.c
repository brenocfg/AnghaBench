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
struct loop {int /*<<< orphan*/  header; int /*<<< orphan*/  latch; } ;
typedef  int /*<<< orphan*/  edge ;

/* Variables and functions */
 int /*<<< orphan*/  find_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

edge
loop_latch_edge (const struct loop *loop)
{
  return find_edge (loop->latch, loop->header);
}