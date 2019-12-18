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
struct hlist_head {int dummy; } ;
struct dlm_ctxt {struct hlist_head** lockres_hash; } ;

/* Variables and functions */
 unsigned int DLM_BUCKETS_PER_PAGE ; 
 unsigned int DLM_HASH_PAGES ; 

__attribute__((used)) static inline struct hlist_head *dlm_lockres_hash(struct dlm_ctxt *dlm, unsigned i)
{
	return dlm->lockres_hash[(i / DLM_BUCKETS_PER_PAGE) % DLM_HASH_PAGES] + (i % DLM_BUCKETS_PER_PAGE);
}