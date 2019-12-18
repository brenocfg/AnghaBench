#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct netplay_input_state {int dummy; } ;
typedef  TYPE_1__* netplay_input_state_t ;
struct TYPE_4__ {int used; size_t size; scalar_t__ client_num; struct TYPE_4__* next; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

netplay_input_state_t netplay_input_state_for(netplay_input_state_t *list,
      uint32_t client_num, size_t size, bool must_create, bool must_not_create)
{
   netplay_input_state_t ret;
   while (*list)
   {
      ret = *list;
      if (!ret->used && !must_not_create && ret->size == size)
      {
         ret->client_num = client_num;
         ret->used = true;
         memset(ret->data, 0, size*sizeof(uint32_t));
         return ret;
      }
      else if (ret->used && ret->client_num == client_num)
      {
         if (!must_create && ret->size == size)
            return ret;
         return NULL;
      }
      list = &(ret->next);
   }

   if (must_not_create)
      return NULL;

   /* Couldn't find a slot, allocate a fresh one */
   ret = (netplay_input_state_t)calloc(1, sizeof(struct netplay_input_state) + (size-1) * sizeof(uint32_t));
   if (!ret)
      return NULL;
   *list           = ret;
   ret->client_num = client_num;
   ret->used       = true;
   ret->size       = (uint32_t)size;
   return ret;
}