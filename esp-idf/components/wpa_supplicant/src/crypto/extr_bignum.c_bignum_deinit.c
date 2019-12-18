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
struct bignum {int dummy; } ;
typedef  int /*<<< orphan*/  mp_int ;

/* Variables and functions */
 int /*<<< orphan*/  mp_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct bignum*) ; 

void 
bignum_deinit(struct bignum *n)
{
	if (n) {
		mp_clear((mp_int *) n);
		os_free(n);
	}
}