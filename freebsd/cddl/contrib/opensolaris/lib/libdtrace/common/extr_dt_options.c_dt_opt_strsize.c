#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
typedef  void* dtrace_optval_t ;
struct TYPE_10__ {void* dt_ctferr; void** dt_options; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
struct TYPE_11__ {scalar_t__ ctr_nelems; } ;
typedef  TYPE_2__ ctf_arinfo_t ;

/* Variables and functions */
 scalar_t__ CTF_ERR ; 
 int /*<<< orphan*/ * DT_STR_CTFP (TYPE_1__*) ; 
 int /*<<< orphan*/  DT_STR_TYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  EDT_CTF ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 void* UINT_MAX ; 
 scalar_t__ ctf_array_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 void* ctf_errno (int /*<<< orphan*/ *) ; 
 scalar_t__ ctf_set_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ctf_type_resolve (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ctf_update (int /*<<< orphan*/ *) ; 
 scalar_t__ dt_opt_size (TYPE_1__*,char const*,uintptr_t) ; 
 int dt_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dt_opt_strsize(dtrace_hdl_t *dtp, const char *arg, uintptr_t option)
{
	dtrace_optval_t val = dtp->dt_options[option];
	ctf_file_t *fp = DT_STR_CTFP(dtp);
	ctf_id_t type = ctf_type_resolve(fp, DT_STR_TYPE(dtp));
	ctf_arinfo_t r;

	if (dt_opt_size(dtp, arg, option) != 0)
		return (-1); /* dt_errno is set for us */

	if (dtp->dt_options[option] > UINT_MAX) {
		dtp->dt_options[option] = val;
		return (dt_set_errno(dtp, EOVERFLOW));
	}

	if (ctf_array_info(fp, type, &r) == CTF_ERR) {
		dtp->dt_options[option] = val;
		dtp->dt_ctferr = ctf_errno(fp);
		return (dt_set_errno(dtp, EDT_CTF));
	}

	r.ctr_nelems = (uint_t)dtp->dt_options[option];

	if (ctf_set_array(fp, type, &r) == CTF_ERR ||
	    ctf_update(fp) == CTF_ERR) {
		dtp->dt_options[option] = val;
		dtp->dt_ctferr = ctf_errno(fp);
		return (dt_set_errno(dtp, EDT_CTF));
	}

	return (0);
}