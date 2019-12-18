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
struct ustr {int u_len; int /*<<< orphan*/  u_name; int /*<<< orphan*/  u_cmpID; } ;
typedef  int /*<<< orphan*/  dstring ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct ustr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int udf_build_ustr_exact(struct ustr *dest, dstring *ptr, int exactsize)
{
	if ((!dest) || (!ptr) || (!exactsize))
		return -1;

	memset(dest, 0, sizeof(struct ustr));
	dest->u_cmpID = ptr[0];
	dest->u_len = exactsize - 1;
	memcpy(dest->u_name, ptr + 1, exactsize - 1);

	return 0;
}