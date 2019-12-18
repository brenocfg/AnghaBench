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
 int /*<<< orphan*/  __blk_end_request_cur (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pf_req ; 

__attribute__((used)) static void pf_end_request(int err)
{
	if (pf_req && !__blk_end_request_cur(pf_req, err))
		pf_req = NULL;
}