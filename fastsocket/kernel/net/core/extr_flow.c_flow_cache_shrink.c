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
struct flow_cache_percpu {int dummy; } ;
struct flow_cache {int low_watermark; } ;

/* Variables and functions */
 int /*<<< orphan*/  __flow_cache_shrink (struct flow_cache*,struct flow_cache_percpu*,int) ; 
 int flow_cache_hash_size (struct flow_cache*) ; 

__attribute__((used)) static void flow_cache_shrink(struct flow_cache *fc,
			      struct flow_cache_percpu *fcp)
{
	int shrink_to = fc->low_watermark / flow_cache_hash_size(fc);

	__flow_cache_shrink(fc, fcp, shrink_to);
}