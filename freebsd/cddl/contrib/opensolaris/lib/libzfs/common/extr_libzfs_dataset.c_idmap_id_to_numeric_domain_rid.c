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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int idmap_stat ;
typedef  int /*<<< orphan*/  idmap_rid_t ;
typedef  int /*<<< orphan*/  idmap_get_handle_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IDMAP_REQ_FLG_USE_CACHE ; 
 int IDMAP_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int idmap_get_create (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  idmap_get_destroy (int /*<<< orphan*/ *) ; 
 int idmap_get_mappings (int /*<<< orphan*/ *) ; 
 int idmap_get_sidbygid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *,int*) ; 
 int idmap_get_sidbyuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int
idmap_id_to_numeric_domain_rid(uid_t id, boolean_t isuser,
    char **domainp, idmap_rid_t *ridp)
{
#ifdef illumos
	idmap_get_handle_t *get_hdl = NULL;
	idmap_stat status;
	int err = EINVAL;

	if (idmap_get_create(&get_hdl) != IDMAP_SUCCESS)
		goto out;

	if (isuser) {
		err = idmap_get_sidbyuid(get_hdl, id,
		    IDMAP_REQ_FLG_USE_CACHE, domainp, ridp, &status);
	} else {
		err = idmap_get_sidbygid(get_hdl, id,
		    IDMAP_REQ_FLG_USE_CACHE, domainp, ridp, &status);
	}
	if (err == IDMAP_SUCCESS &&
	    idmap_get_mappings(get_hdl) == IDMAP_SUCCESS &&
	    status == IDMAP_SUCCESS)
		err = 0;
	else
		err = EINVAL;
out:
	if (get_hdl)
		idmap_get_destroy(get_hdl);
	return (err);
#else	/* !illumos */
	assert(!"invalid code path");
	return (EINVAL); // silence compiler warning
#endif	/* illumos */
}