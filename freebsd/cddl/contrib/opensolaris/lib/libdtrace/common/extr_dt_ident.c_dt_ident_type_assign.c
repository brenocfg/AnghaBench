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
struct TYPE_3__ {int /*<<< orphan*/  di_type; int /*<<< orphan*/ * di_ctfp; } ;
typedef  TYPE_1__ dt_ident_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;

/* Variables and functions */

void
dt_ident_type_assign(dt_ident_t *idp, ctf_file_t *fp, ctf_id_t type)
{
	idp->di_ctfp = fp;
	idp->di_type = type;
}