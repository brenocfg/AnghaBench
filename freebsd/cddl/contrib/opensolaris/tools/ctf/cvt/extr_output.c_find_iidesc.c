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
typedef  int /*<<< orphan*/  tdata_t ;
typedef  int /*<<< orphan*/  iidesc_t ;
struct TYPE_4__ {int /*<<< orphan*/ * iim_ret; int /*<<< orphan*/  iim_name; } ;
typedef  TYPE_1__ iidesc_match_t ;

/* Variables and functions */
 int /*<<< orphan*/  iter_iidescs_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  matching_iidesc ; 

__attribute__((used)) static iidesc_t *
find_iidesc(tdata_t *td, iidesc_match_t *match)
{
	match->iim_ret = NULL;
	iter_iidescs_by_name(td, match->iim_name,
	    matching_iidesc, match);
	return (match->iim_ret);
}