#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ refcount; struct TYPE_5__* next; } ;
typedef  TYPE_1__ VCOS_LOG_CAT_T ;

/* Variables and functions */
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_platform_unregister (TYPE_1__*) ; 
 TYPE_1__* vcos_logging_categories ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

void vcos_log_unregister(VCOS_LOG_CAT_T *category)
{
   VCOS_LOG_CAT_T **pcat;

   vcos_mutex_lock(&lock);
   category->refcount--;
   if (category->refcount == 0)
   {
      pcat = &vcos_logging_categories;
      while (*pcat != category)
      {
         if (!*pcat)
            break;   /* possibly deregistered twice? */
         if ((*pcat)->next == NULL)
         {
            vcos_assert(0); /* already removed! */
            vcos_mutex_unlock(&lock);
            return;
         }
         pcat = &(*pcat)->next;
      }
      if (*pcat)
         *pcat = category->next;

      vcos_log_platform_unregister(category);
   }
   vcos_mutex_unlock(&lock);
}