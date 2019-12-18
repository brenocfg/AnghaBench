#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ x; struct TYPE_8__* next; void* y; } ;
typedef  TYPE_1__ stbrp_node ;
typedef  void* stbrp_coord ;
struct TYPE_9__ {scalar_t__ height; TYPE_1__* free_head; } ;
typedef  TYPE_2__ stbrp_context ;
struct TYPE_10__ {scalar_t__ y; scalar_t__ x; TYPE_1__** prev_link; } ;
typedef  TYPE_3__ stbrp__findresult ;

/* Variables and functions */
 TYPE_3__ stbrp__skyline_find_best_pos (TYPE_2__*,int,int) ; 

__attribute__((used)) static stbrp__findresult stbrp__skyline_pack_rectangle(stbrp_context *context, int width, int height)
{
   /* find best position according to heuristic */
   stbrp_node *node, *cur;
   stbrp__findresult res = stbrp__skyline_find_best_pos(context, width, height);

   /* bail if:
    *    1. it failed
    *    2. the best node doesn't fit (we don't always check this)
    *    3. we're out of memory
    */
   if (res.prev_link == NULL || res.y + height > context->height || context->free_head == NULL)
   {
      res.prev_link = NULL;
      return res;
   }

   /* on success, create new node */
   node = context->free_head;
   node->x = (stbrp_coord) res.x;
   node->y = (stbrp_coord) (res.y + height);

   context->free_head = node->next;

   /* insert the new node into the right starting point, and
    * let 'cur' point to the remaining nodes needing to be
    * stiched back in
    */

   cur = *res.prev_link;
   if (cur->x < res.x)
   {
      /* preserve the existing one, so start testing with the next one */
      stbrp_node *next = cur->next;
      cur->next = node;
      cur = next;
   }
   else
      *res.prev_link = node;

   /* from here, traverse cur and free the nodes, until we get to one
    * that shouldn't be freed */
   while (cur->next && cur->next->x <= res.x + width)
   {
      stbrp_node *next = cur->next;

      /* move the current node to the free list */
      cur->next = context->free_head;
      context->free_head = cur;
      cur = next;
   }

   /* stitch the list back in */
   node->next = cur;

   if (cur->x < res.x + width)
      cur->x = (stbrp_coord) (res.x + width);

   return res;
}