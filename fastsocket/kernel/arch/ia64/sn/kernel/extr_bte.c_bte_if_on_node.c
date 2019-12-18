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
struct bteinfo_s {int dummy; } ;
struct TYPE_3__ {struct bteinfo_s* bte_if; } ;
typedef  TYPE_1__ nodepda_t ;
typedef  int /*<<< orphan*/  nasid_t ;

/* Variables and functions */
 TYPE_1__* NODEPDA (int) ; 
 int nasid_to_cnodeid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct bteinfo_s *bte_if_on_node(nasid_t nasid, int interface)
{
	nodepda_t *tmp_nodepda;

	if (nasid_to_cnodeid(nasid) == -1)
		return (struct bteinfo_s *)NULL;

	tmp_nodepda = NODEPDA(nasid_to_cnodeid(nasid));
	return &tmp_nodepda->bte_if[interface];

}