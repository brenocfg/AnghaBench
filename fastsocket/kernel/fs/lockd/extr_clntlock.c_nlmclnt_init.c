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
struct nlmclnt_initdata {int nfs_version; int /*<<< orphan*/  noresvport; int /*<<< orphan*/  hostname; int /*<<< orphan*/  protocol; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  address; } ;
struct nlm_host {int dummy; } ;

/* Variables and functions */
 int ENOLCK ; 
 struct nlm_host* ERR_PTR (int) ; 
 int /*<<< orphan*/  lockd_down () ; 
 int lockd_up () ; 
 struct nlm_host* nlmclnt_lookup_host (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct nlm_host *nlmclnt_init(const struct nlmclnt_initdata *nlm_init)
{
	struct nlm_host *host;
	u32 nlm_version = (nlm_init->nfs_version == 2) ? 1 : 4;
	int status;

	status = lockd_up();
	if (status < 0)
		return ERR_PTR(status);

	host = nlmclnt_lookup_host(nlm_init->address, nlm_init->addrlen,
				   nlm_init->protocol, nlm_version,
				   nlm_init->hostname, nlm_init->noresvport);
	if (host == NULL) {
		lockd_down();
		return ERR_PTR(-ENOLCK);
	}

	return host;
}