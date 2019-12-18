#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int dn_flags; int /*<<< orphan*/  dn_type; int /*<<< orphan*/  dn_ctfp; int /*<<< orphan*/ * dn_ident; } ;
typedef  TYPE_1__ dt_node_t ;
struct TYPE_6__ {int /*<<< orphan*/  di_kind; } ;

/* Variables and functions */
 int DT_NF_USERLAND ; 
 TYPE_4__* dt_ident_resolve (int /*<<< orphan*/ *) ; 
 char* dt_idkind_name (int /*<<< orphan*/ ) ; 
 scalar_t__ dt_node_is_dynamic (TYPE_1__ const*) ; 
 char const* dt_type_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 size_t snprintf (char*,size_t,char*,...) ; 

const char *
dt_node_type_name(const dt_node_t *dnp, char *buf, size_t len)
{
	if (dt_node_is_dynamic(dnp) && dnp->dn_ident != NULL) {
		(void) snprintf(buf, len, "%s",
		    dt_idkind_name(dt_ident_resolve(dnp->dn_ident)->di_kind));
		return (buf);
	}

	if (dnp->dn_flags & DT_NF_USERLAND) {
		size_t n = snprintf(buf, len, "userland ");
		len = len > n ? len - n : 0;
		(void) dt_type_name(dnp->dn_ctfp, dnp->dn_type, buf + n, len);
		return (buf);
	}

	return (dt_type_name(dnp->dn_ctfp, dnp->dn_type, buf, len));
}