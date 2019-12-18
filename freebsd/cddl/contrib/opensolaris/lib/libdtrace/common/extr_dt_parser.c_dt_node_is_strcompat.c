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
struct TYPE_5__ {int dn_flags; int /*<<< orphan*/  dn_type; int /*<<< orphan*/ * dn_ctfp; } ;
typedef  TYPE_1__ dt_node_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
typedef  int /*<<< orphan*/  ctf_encoding_t ;
struct TYPE_6__ {int /*<<< orphan*/  ctr_contents; } ;
typedef  TYPE_2__ ctf_arinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_ERR ; 
 scalar_t__ CTF_K_ARRAY ; 
 scalar_t__ CTF_K_POINTER ; 
 int DT_NF_COOKED ; 
 scalar_t__ IS_CHAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ctf_array_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ ctf_type_encoding (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ctf_type_kind (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_reference (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_resolve (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
dt_node_is_strcompat(const dt_node_t *dnp)
{
	ctf_file_t *fp = dnp->dn_ctfp;
	ctf_encoding_t e;
	ctf_arinfo_t r;
	ctf_id_t base;
	uint_t kind;

	assert(dnp->dn_flags & DT_NF_COOKED);

	base = ctf_type_resolve(fp, dnp->dn_type);
	kind = ctf_type_kind(fp, base);

	if (kind == CTF_K_POINTER &&
	    (base = ctf_type_reference(fp, base)) != CTF_ERR &&
	    (base = ctf_type_resolve(fp, base)) != CTF_ERR &&
	    ctf_type_encoding(fp, base, &e) == 0 && IS_CHAR(e))
		return (1); /* promote char pointer to string */

	if (kind == CTF_K_ARRAY && ctf_array_info(fp, base, &r) == 0 &&
	    (base = ctf_type_resolve(fp, r.ctr_contents)) != CTF_ERR &&
	    ctf_type_encoding(fp, base, &e) == 0 && IS_CHAR(e))
		return (1); /* promote char array to string */

	return (0);
}