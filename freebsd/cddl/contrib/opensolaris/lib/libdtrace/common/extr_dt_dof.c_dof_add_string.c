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
struct TYPE_3__ {int /*<<< orphan*/  ddo_hdl; int /*<<< orphan*/  ddo_strs; } ;
typedef  TYPE_1__ dt_dof_t ;
typedef  int /*<<< orphan*/  dt_buf_t ;
typedef  scalar_t__ dof_stridx_t ;

/* Variables and functions */
 scalar_t__ dt_buf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dt_buf_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,scalar_t__,int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static dof_stridx_t
dof_add_string(dt_dof_t *ddo, const char *s)
{
	dt_buf_t *bp = &ddo->ddo_strs;
	dof_stridx_t i = dt_buf_len(bp);

	if (i != 0 && (s == NULL || *s == '\0'))
		return (0); /* string table has \0 at offset 0 */

	dt_buf_write(ddo->ddo_hdl, bp, s, strlen(s) + 1, sizeof (char));
	return (i);
}