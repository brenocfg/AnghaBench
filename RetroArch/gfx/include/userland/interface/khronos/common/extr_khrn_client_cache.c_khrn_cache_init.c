#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * next; TYPE_1__* prev; } ;
struct TYPE_5__ {TYPE_2__* next; int /*<<< orphan*/ * prev; } ;
struct TYPE_7__ {int /*<<< orphan*/  map; TYPE_2__ end; TYPE_1__ start; scalar_t__ server_depth; scalar_t__ client_depth; int /*<<< orphan*/ * data; int /*<<< orphan*/ * tree; } ;
typedef  TYPE_3__ KHRN_CACHE_T ;

/* Variables and functions */
 int khrn_pointer_map_init (int /*<<< orphan*/ *,int) ; 

int khrn_cache_init(KHRN_CACHE_T *cache)
{
   cache->tree = NULL;
   cache->data = NULL;

   cache->client_depth = 0;
   cache->server_depth = 0;

   cache->start.prev = NULL;
   cache->start.next = &cache->end;
   cache->end.prev = &cache->start;
   cache->end.next = NULL;

   return khrn_pointer_map_init(&cache->map, 64);
}