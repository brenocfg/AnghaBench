#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_6__ {struct TYPE_6__* prev; struct TYPE_6__* next; } ;
struct TYPE_5__ {int server_depth; int client_depth; scalar_t__* tree; scalar_t__* data; TYPE_2__ end; TYPE_2__ start; int /*<<< orphan*/  map; } ;
typedef  TYPE_1__ KHRN_CACHE_T ;
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;
typedef  TYPE_2__ CACHE_LINK_T ;

/* Variables and functions */
 int CACHE_LOG2_BLOCK_SIZE ; 
 scalar_t__ CACHE_MAX_DEPTH ; 
 int _msb (int) ; 
 int /*<<< orphan*/  callback ; 
 int /*<<< orphan*/  khrn_platform_free (scalar_t__*) ; 
 scalar_t__ khrn_platform_malloc (int,char*) ; 
 int /*<<< orphan*/  khrn_pointer_map_iterate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__**) ; 
 int /*<<< orphan*/  platform_memcpy (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ relocate (TYPE_2__*,scalar_t__**) ; 
 scalar_t__ send_grow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tree_init (scalar_t__*,int) ; 

__attribute__((used)) static int grow(CLIENT_THREAD_STATE_T *thread, KHRN_CACHE_T *cache)
{
   /*
      try to grow the server cache
   */

   uint8_t *tree;
   uint8_t *data;
   int i;

   if (cache->server_depth == cache->client_depth) {
      if (cache->server_depth < CACHE_MAX_DEPTH && send_grow(thread))
         cache->server_depth++;
      else
         return 0;
   }

   tree = (uint8_t *)khrn_platform_malloc(1 << (cache->client_depth + 1), "KHRN_CACHE_T.tree");
   data = (uint8_t *)khrn_platform_malloc(1 << (cache->client_depth + CACHE_LOG2_BLOCK_SIZE), "KHRN_CACHE_T.data");

   if (!tree || !data) {
      khrn_platform_free(tree);
      khrn_platform_free(data);
      return 0;
   }

   /*
      set up new tree structure
   */

   tree_init(tree, cache->client_depth + 1);

   if (cache->client_depth) {
      for (i = 1; i < 1 << cache->client_depth; i++)
         tree[i ^ 3 << _msb(i)] = cache->tree[i];

      tree[1] = tree[3] + (tree[2] == tree[3]);
   }

   /*
      relocate pointermap and linked list pointers
   */
   {
      uint8_t *user[2];
	  user[0] = cache->data;
	  user[1] = data;

      khrn_pointer_map_iterate(&cache->map, callback, user);

      cache->start.next->prev = &cache->start;
      if (cache->start.next != &cache->end)
         cache->start.next = (CACHE_LINK_T *)relocate(cache->start.next, user);

      cache->end.prev->next = &cache->end;
      if (cache->end.prev != &cache->start)
         cache->end.prev = (CACHE_LINK_T *)relocate(cache->end.prev, user);
   }

   /*
      set up new data block
   */

   if (cache->data)
      platform_memcpy(data, cache->data, 1 << (cache->client_depth + CACHE_LOG2_BLOCK_SIZE - 1));

   /*
      free old blocks, update structure
   */

   khrn_platform_free(cache->tree);
   khrn_platform_free(cache->data);

   cache->tree = tree;
   cache->data = data;

   cache->client_depth++;

   return 1;
}