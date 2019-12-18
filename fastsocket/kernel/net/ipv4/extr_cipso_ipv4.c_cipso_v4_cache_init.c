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
typedef  size_t u32 ;
struct cipso_v4_map_cache_bkt {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; scalar_t__ size; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 size_t CIPSO_V4_CACHE_BUCKETS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_1__* cipso_v4_cache ; 
 TYPE_1__* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cipso_v4_cache_init(void)
{
	u32 iter;

	cipso_v4_cache = kcalloc(CIPSO_V4_CACHE_BUCKETS,
				 sizeof(struct cipso_v4_map_cache_bkt),
				 GFP_KERNEL);
	if (cipso_v4_cache == NULL)
		return -ENOMEM;

	for (iter = 0; iter < CIPSO_V4_CACHE_BUCKETS; iter++) {
		spin_lock_init(&cipso_v4_cache[iter].lock);
		cipso_v4_cache[iter].size = 0;
		INIT_LIST_HEAD(&cipso_v4_cache[iter].list);
	}

	return 0;
}