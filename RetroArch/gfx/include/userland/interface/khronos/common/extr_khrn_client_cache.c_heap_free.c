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
struct TYPE_3__ {int client_depth; int* tree; } ;
typedef  TYPE_1__ KHRN_CACHE_T ;

/* Variables and functions */

__attribute__((used)) static void heap_free(KHRN_CACHE_T *cache, int block)
{
   int node = block + (1 << (cache->client_depth - 1));
   int reset = 1;

   while (cache->tree[node] > 0) {
      node >>= 1;
      reset++;
   }

   cache->tree[node] = reset;

   while (cache->tree[node] == cache->tree[node ^ 1]) {
      node >>= 1;
      cache->tree[node] = cache->tree[node] + 1;
   }

   while (cache->tree[node] > cache->tree[node >> 1]) {
      cache->tree[node >> 1] = cache->tree[node];
      node >>= 1;
   }
}