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
typedef  int /*<<< orphan*/  cc_unit ;
typedef  int /*<<< orphan*/  cc_size ;

/* Variables and functions */
 int /*<<< orphan*/  CC_MEMMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccn_sizeof_n (int /*<<< orphan*/ ) ; 

void ccn_set(cc_size n, cc_unit *r, const cc_unit *s)
{
    CC_MEMMOVE(r, s, ccn_sizeof_n(n));
}