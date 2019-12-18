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
typedef  TYPE_1__* sys_mbox_t ;
struct sys_mbox_s {int dummy; } ;
typedef  int /*<<< orphan*/  err_t ;
struct TYPE_5__ {int /*<<< orphan*/ * os_mbox; int /*<<< orphan*/ * owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_MEM ; 
 int /*<<< orphan*/  ERR_OK ; 
 int /*<<< orphan*/  ESP_THREAD_SAFE_DEBUG ; 
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* mem_malloc (int) ; 
 int /*<<< orphan*/ * xQueueCreate (int,int) ; 

err_t
sys_mbox_new(sys_mbox_t *mbox, int size)
{
  *mbox = mem_malloc(sizeof(struct sys_mbox_s));
  if (*mbox == NULL){
    LWIP_DEBUGF(ESP_THREAD_SAFE_DEBUG, ("fail to new *mbox\n"));
    return ERR_MEM;
  }

  (*mbox)->os_mbox = xQueueCreate(size, sizeof(void *));

  if ((*mbox)->os_mbox == NULL) {
    LWIP_DEBUGF(ESP_THREAD_SAFE_DEBUG, ("fail to new (*mbox)->os_mbox\n"));
    free(*mbox);
    return ERR_MEM;
  }

#if ESP_THREAD_SAFE
  (*mbox)->owner = NULL;
#endif

  LWIP_DEBUGF(ESP_THREAD_SAFE_DEBUG, ("new *mbox ok mbox=%p os_mbox=%p\n", *mbox, (*mbox)->os_mbox));
  return ERR_OK;
}