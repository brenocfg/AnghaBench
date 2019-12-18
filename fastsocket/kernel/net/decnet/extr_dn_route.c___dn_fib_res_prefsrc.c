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
struct dn_fib_res {int /*<<< orphan*/  scope; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  DN_FIB_RES_DEV (struct dn_fib_res) ; 
 int /*<<< orphan*/  DN_FIB_RES_GW (struct dn_fib_res) ; 
 int /*<<< orphan*/  dnet_select_source (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __le16 __dn_fib_res_prefsrc(struct dn_fib_res *res)
{
	return dnet_select_source(DN_FIB_RES_DEV(*res), DN_FIB_RES_GW(*res), res->scope);
}