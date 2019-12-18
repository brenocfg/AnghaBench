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
typedef  int u32 ;
struct threshold_block_cross_cpu {scalar_t__ retval; struct threshold_block* tb; } ;
struct threshold_block {scalar_t__ threshold_limit; int /*<<< orphan*/  address; } ;

/* Variables and functions */
 scalar_t__ THRESHOLD_MAX ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void local_error_count_handler(void *_tbcc)
{
	struct threshold_block_cross_cpu *tbcc = _tbcc;
	struct threshold_block *b = tbcc->tb;
	u32 low, high;

	rdmsr(b->address, low, high);
	tbcc->retval = (high & 0xFFF) - (THRESHOLD_MAX - b->threshold_limit);
}