#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* lca_name; int /*<<< orphan*/ * lca_info; } ;
typedef  TYPE_1__ linfo_cb_arg_t ;
typedef  int /*<<< orphan*/  ctf_lblinfo_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;

/* Variables and functions */
 int CTF_ERR ; 
 int /*<<< orphan*/  ECTF_NOLABEL ; 
 int ctf_label_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int ctf_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  label_info_cb ; 

int
ctf_label_info(ctf_file_t *fp, const char *lname, ctf_lblinfo_t *linfo)
{
	linfo_cb_arg_t cb_arg;
	int rc;

	cb_arg.lca_name = lname;
	cb_arg.lca_info = linfo;

	if ((rc = ctf_label_iter(fp, label_info_cb, &cb_arg)) == CTF_ERR)
		return (rc);

	if (rc != 1)
		return (ctf_set_errno(fp, ECTF_NOLABEL));

	return (0);
}