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
typedef  int /*<<< orphan*/  n ;
struct TYPE_3__ {scalar_t__ dtt_type; int /*<<< orphan*/ * dtt_ctfp; } ;
typedef  TYPE_1__ dtrace_typeinfo_t ;
typedef  int /*<<< orphan*/  ctf_membinfo_t ;
typedef  scalar_t__ ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;

/* Variables and functions */
 scalar_t__ CTF_ERR ; 
 scalar_t__ CTF_K_FORWARD ; 
 int DT_TYPE_NAMELEN ; 
 scalar_t__ ctf_member_info (int /*<<< orphan*/ *,scalar_t__,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ ctf_type_kind (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * ctf_type_name (int /*<<< orphan*/ *,scalar_t__,char*,int) ; 
 scalar_t__ ctf_type_resolve (int /*<<< orphan*/ *,scalar_t__) ; 
 int dt_type_lookup (char*,TYPE_1__*) ; 

__attribute__((used)) static ctf_file_t *
dt_cg_membinfo(ctf_file_t *fp, ctf_id_t type, const char *s, ctf_membinfo_t *mp)
{
	while (ctf_type_kind(fp, type) == CTF_K_FORWARD) {
		char n[DT_TYPE_NAMELEN];
		dtrace_typeinfo_t dtt;

		if (ctf_type_name(fp, type, n, sizeof (n)) == NULL ||
		    dt_type_lookup(n, &dtt) == -1 || (
		    dtt.dtt_ctfp == fp && dtt.dtt_type == type))
			break; /* unable to improve our position */

		fp = dtt.dtt_ctfp;
		type = ctf_type_resolve(fp, dtt.dtt_type);
	}

	if (ctf_member_info(fp, type, s, mp) == CTF_ERR)
		return (NULL); /* ctf_errno is set for us */

	return (fp);
}