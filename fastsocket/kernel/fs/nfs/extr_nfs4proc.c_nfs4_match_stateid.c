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
typedef  int /*<<< orphan*/  nfs4_stateid ;

/* Variables and functions */
 int nfs4_stateid_match (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static bool nfs4_match_stateid(const nfs4_stateid *s1,
		const nfs4_stateid *s2)
{
	return nfs4_stateid_match(s1, s2);
}