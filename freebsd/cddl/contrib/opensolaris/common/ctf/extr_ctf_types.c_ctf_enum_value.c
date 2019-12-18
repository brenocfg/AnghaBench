#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_5__ {int /*<<< orphan*/  ctt_info; } ;
typedef  TYPE_1__ ctf_type_t ;
typedef  int ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
struct TYPE_6__ {int cte_value; int /*<<< orphan*/  cte_name; } ;
typedef  TYPE_2__ ctf_enum_t ;

/* Variables and functions */
 int CTF_ERR ; 
 scalar_t__ CTF_K_ENUM ; 
 int /*<<< orphan*/  ECTF_NOENUMNAM ; 
 int /*<<< orphan*/  ECTF_NOTENUM ; 
 scalar_t__ LCTF_INFO_KIND (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ LCTF_INFO_VLEN (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_get_ctt_size (int /*<<< orphan*/ *,TYPE_1__ const*,scalar_t__*,scalar_t__*) ; 
 TYPE_1__* ctf_lookup_by_id (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  ctf_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_strptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ctf_type_resolve (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int
ctf_enum_value(ctf_file_t *fp, ctf_id_t type, const char *name, int *valp)
{
	ctf_file_t *ofp = fp;
	const ctf_type_t *tp;
	const ctf_enum_t *ep;
	ssize_t size, increment;
	uint_t n;

	if ((type = ctf_type_resolve(fp, type)) == CTF_ERR)
		return (CTF_ERR); /* errno is set for us */

	if ((tp = ctf_lookup_by_id(&fp, type)) == NULL)
		return (CTF_ERR); /* errno is set for us */

	if (LCTF_INFO_KIND(fp, tp->ctt_info) != CTF_K_ENUM) {
		(void) ctf_set_errno(ofp, ECTF_NOTENUM);
		return (CTF_ERR);
	}

	(void) ctf_get_ctt_size(fp, tp, &size, &increment);

	ep = (const ctf_enum_t *)((uintptr_t)tp + increment);

	for (n = LCTF_INFO_VLEN(fp, tp->ctt_info); n != 0; n--, ep++) {
		if (strcmp(ctf_strptr(fp, ep->cte_name), name) == 0) {
			if (valp != NULL)
				*valp = ep->cte_value;
			return (0);
		}
	}

	(void) ctf_set_errno(ofp, ECTF_NOENUMNAM);
	return (CTF_ERR);
}