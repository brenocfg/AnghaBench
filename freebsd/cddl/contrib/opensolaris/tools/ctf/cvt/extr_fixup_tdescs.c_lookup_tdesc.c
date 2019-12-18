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
typedef  int /*<<< orphan*/  tdesc_t ;
typedef  int /*<<< orphan*/  tdata_t ;
struct match {char const* member_1; int /*<<< orphan*/ * m_ret; int /*<<< orphan*/ * member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  iter_iidescs_by_name (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,struct match*) ; 
 int /*<<< orphan*/  matching_iidesc ; 

__attribute__((used)) static tdesc_t *
lookup_tdesc(tdata_t *td, char const *name)
{
	struct match match = { NULL, name };
	iter_iidescs_by_name(td, name, matching_iidesc, &match);
	return (match.m_ret);
}