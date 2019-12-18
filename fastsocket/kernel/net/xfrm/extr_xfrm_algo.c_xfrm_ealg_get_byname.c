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
struct xfrm_algo_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xfrm_alg_name_match ; 
 int /*<<< orphan*/  xfrm_ealg_list ; 
 struct xfrm_algo_desc* xfrm_find_algo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

struct xfrm_algo_desc *xfrm_ealg_get_byname(char *name, int probe)
{
	return xfrm_find_algo(&xfrm_ealg_list, xfrm_alg_name_match, name,
			      probe);
}