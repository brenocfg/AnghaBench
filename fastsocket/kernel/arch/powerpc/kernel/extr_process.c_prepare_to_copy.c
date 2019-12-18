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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  flush_altivec_to_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_fp_to_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_spe_to_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_vsx_to_thread (int /*<<< orphan*/ ) ; 

void prepare_to_copy(struct task_struct *tsk)
{
	flush_fp_to_thread(current);
	flush_altivec_to_thread(current);
	flush_vsx_to_thread(current);
	flush_spe_to_thread(current);
}