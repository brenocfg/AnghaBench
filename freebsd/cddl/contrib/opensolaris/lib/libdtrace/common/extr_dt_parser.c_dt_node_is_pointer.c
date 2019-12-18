#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
struct TYPE_4__ {int dn_flags; int /*<<< orphan*/  dn_type; int /*<<< orphan*/ * dn_ctfp; } ;
typedef  TYPE_1__ dt_node_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;

/* Variables and functions */
 scalar_t__ CTF_K_ARRAY ; 
 scalar_t__ CTF_K_POINTER ; 
 int DT_NF_COOKED ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ctf_type_kind (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_type_resolve (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dt_node_is_string (TYPE_1__ const*) ; 

int
dt_node_is_pointer(const dt_node_t *dnp)
{
	ctf_file_t *fp = dnp->dn_ctfp;
	uint_t kind;

	assert(dnp->dn_flags & DT_NF_COOKED);

	if (dt_node_is_string(dnp))
		return (0); /* string are pass-by-ref but act like structs */

	kind = ctf_type_kind(fp, ctf_type_resolve(fp, dnp->dn_type));
	return (kind == CTF_K_POINTER || kind == CTF_K_ARRAY);
}