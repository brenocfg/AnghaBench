#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfs4_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fmode; scalar_t__ open_flags; } ;
struct nfs4_opendata {int /*<<< orphan*/  c_res; int /*<<< orphan*/  o_res; TYPE_1__ o_arg; } ;
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nfs4_state*) ; 
 int PTR_ERR (struct nfs4_state*) ; 
 int _nfs4_recover_proc_open (struct nfs4_opendata*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs4_close_state (struct nfs4_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_init_opendata_res (struct nfs4_opendata*) ; 
 struct nfs4_state* nfs4_opendata_to_nfs4_state (struct nfs4_opendata*) ; 

__attribute__((used)) static int nfs4_open_recover_helper(struct nfs4_opendata *opendata, fmode_t fmode, struct nfs4_state **res)
{
	struct nfs4_state *newstate;
	int ret;

	opendata->o_arg.open_flags = 0;
	opendata->o_arg.fmode = fmode;
	memset(&opendata->o_res, 0, sizeof(opendata->o_res));
	memset(&opendata->c_res, 0, sizeof(opendata->c_res));
	nfs4_init_opendata_res(opendata);
	ret = _nfs4_recover_proc_open(opendata);
	if (ret != 0)
		return ret; 
	newstate = nfs4_opendata_to_nfs4_state(opendata);
	if (IS_ERR(newstate))
		return PTR_ERR(newstate);
	nfs4_close_state(newstate, fmode);
	*res = newstate;
	return 0;
}