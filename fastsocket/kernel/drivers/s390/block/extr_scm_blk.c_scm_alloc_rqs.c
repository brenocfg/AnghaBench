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

/* Variables and functions */
 int __scm_alloc_rq () ; 

__attribute__((used)) static int scm_alloc_rqs(unsigned int nrqs)
{
	int ret = 0;

	while (nrqs-- && !ret)
		ret = __scm_alloc_rq();

	return ret;
}