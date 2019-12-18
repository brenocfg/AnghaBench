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
struct dccp_ackvec {int /*<<< orphan*/  av_records; scalar_t__ av_vec_len; int /*<<< orphan*/  av_time; scalar_t__ av_buf_nonce; scalar_t__ av_buf_ackno; scalar_t__ av_buf_head; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ DCCP_MAX_ACKVEC_LEN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ UINT48_MAX ; 
 int /*<<< orphan*/  dccp_ackvec_slab ; 
 struct dccp_ackvec* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct dccp_ackvec *dccp_ackvec_alloc(const gfp_t priority)
{
	struct dccp_ackvec *av = kmem_cache_alloc(dccp_ackvec_slab, priority);

	if (av != NULL) {
		av->av_buf_head	 = DCCP_MAX_ACKVEC_LEN - 1;
		av->av_buf_ackno = UINT48_MAX + 1;
		av->av_buf_nonce = 0;
		av->av_time	 = ktime_set(0, 0);
		av->av_vec_len	 = 0;
		INIT_LIST_HEAD(&av->av_records);
	}

	return av;
}