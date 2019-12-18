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
struct TYPE_3__ {int /*<<< orphan*/  map; int /*<<< orphan*/  data; int /*<<< orphan*/  tree; } ;
typedef  TYPE_1__ KHRN_CACHE_T ;

/* Variables and functions */
 int /*<<< orphan*/  khrn_platform_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  khrn_pointer_map_term (int /*<<< orphan*/ *) ; 

void khrn_cache_term(KHRN_CACHE_T *cache)
{
   khrn_platform_free(cache->tree);
   khrn_platform_free(cache->data);

   khrn_pointer_map_term(&cache->map);
}