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
struct TYPE_4__ {scalar_t__ dd_kind; int dd_attr; int /*<<< orphan*/ * dd_name; } ;
typedef  TYPE_1__ dt_decl_t ;

/* Variables and functions */
 scalar_t__ CTF_K_FLOAT ; 
 scalar_t__ CTF_K_INTEGER ; 
 scalar_t__ CTF_K_UNKNOWN ; 
 int DT_DA_LONG ; 
 int DT_DA_LONGLONG ; 
 int DT_DA_SHORT ; 
 int DT_DA_SIGNED ; 
 int DT_DA_UNSIGNED ; 
 int /*<<< orphan*/  D_DECL_CHARATTR ; 
 int /*<<< orphan*/  D_DECL_LONGINT ; 
 int /*<<< orphan*/  D_DECL_SIGNINT ; 
 int /*<<< orphan*/  D_DECL_VOIDATTR ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static dt_decl_t *
dt_decl_check(dt_decl_t *ddp)
{
	if (ddp->dd_kind == CTF_K_UNKNOWN)
		return (ddp); /* nothing to check if the type is not yet set */

	if (ddp->dd_name != NULL && strcmp(ddp->dd_name, "char") == 0 &&
	    (ddp->dd_attr & (DT_DA_SHORT | DT_DA_LONG | DT_DA_LONGLONG))) {
		xyerror(D_DECL_CHARATTR, "invalid type declaration: short and "
		    "long may not be used with char type\n");
	}

	if (ddp->dd_name != NULL && strcmp(ddp->dd_name, "void") == 0 &&
	    (ddp->dd_attr & (DT_DA_SHORT | DT_DA_LONG | DT_DA_LONGLONG |
	    (DT_DA_SIGNED | DT_DA_UNSIGNED)))) {
		xyerror(D_DECL_VOIDATTR, "invalid type declaration: attributes "
		    "may not be used with void type\n");
	}

	if (ddp->dd_kind != CTF_K_INTEGER &&
	    (ddp->dd_attr & (DT_DA_SIGNED | DT_DA_UNSIGNED))) {
		xyerror(D_DECL_SIGNINT, "invalid type declaration: signed and "
		    "unsigned may only be used with integer type\n");
	}

	if (ddp->dd_kind != CTF_K_INTEGER && ddp->dd_kind != CTF_K_FLOAT &&
	    (ddp->dd_attr & (DT_DA_LONG | DT_DA_LONGLONG))) {
		xyerror(D_DECL_LONGINT, "invalid type declaration: long and "
		    "long long may only be used with integer or "
		    "floating-point type\n");
	}

	return (ddp);
}