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
typedef  int /*<<< orphan*/  ctf_visit_f ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;

/* Variables and functions */
 int ctf_type_rvisit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ctf_type_visit(ctf_file_t *fp, ctf_id_t type, ctf_visit_f *func, void *arg)
{
	return (ctf_type_rvisit(fp, type, func, arg, "", 0, 0));
}