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
struct dlm_ls {int dummy; } ;
struct dlm_lkb {int dummy; } ;

/* Variables and functions */
 int is_master_copy (struct dlm_lkb*) ; 

__attribute__((used)) static int purge_mstcpy_test(struct dlm_ls *ls, struct dlm_lkb *lkb)
{
	return is_master_copy(lkb);
}