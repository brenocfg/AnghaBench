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
typedef  int /*<<< orphan*/  dt_pfargv_t ;
typedef  int /*<<< orphan*/  dt_pfargd_t ;
struct TYPE_3__ {int /*<<< orphan*/  dn_type; int /*<<< orphan*/ * dn_ctfp; } ;
typedef  TYPE_1__ dt_node_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;

/* Variables and functions */
 scalar_t__ CTF_K_TYPEDEF ; 
 int DT_TYPE_NAMELEN ; 
 scalar_t__ ctf_type_kind (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ctf_type_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ctf_type_reference (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_resolve (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
pfcheck_xlonglong(dt_pfargv_t *pfv, dt_pfargd_t *pfd, dt_node_t *dnp)
{
	ctf_file_t *ctfp = dnp->dn_ctfp;
	ctf_id_t type = dnp->dn_type;
	char n[DT_TYPE_NAMELEN];

	if (ctf_type_name(ctfp, ctf_type_resolve(ctfp, type), n,
	    sizeof (n)) != NULL && (strcmp(n, "long long") == 0 ||
	    strcmp(n, "signed long long") == 0 ||
	    strcmp(n, "unsigned long long") == 0))
		return (1);

	/*
	 * If the type used for %llx or %llX is not an [unsigned] long long, we
	 * also permit it to be a [u]int64_t or any typedef thereof.  We know
	 * that these typedefs are guaranteed to work with %ll[xX] in either
	 * compilation environment even though they alias to "long" in LP64.
	 */
	while (ctf_type_kind(ctfp, type) == CTF_K_TYPEDEF) {
		if (ctf_type_name(ctfp, type, n, sizeof (n)) != NULL &&
		    (strcmp(n, "int64_t") == 0 || strcmp(n, "uint64_t") == 0))
			return (1);

		type = ctf_type_reference(ctfp, type);
	}

	return (0);
}