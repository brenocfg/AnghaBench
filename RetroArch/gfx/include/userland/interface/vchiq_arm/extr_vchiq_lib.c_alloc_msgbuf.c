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

/* Variables and functions */
 int /*<<< orphan*/  MSGBUF_SIZE ; 
 void* free_msgbufs ; 
 int /*<<< orphan*/  vchiq_lib_mutex ; 
 void* vcos_malloc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
alloc_msgbuf(void)
{
   void *msgbuf;
   vcos_mutex_lock(&vchiq_lib_mutex);
   msgbuf = free_msgbufs;
   if (msgbuf)
      free_msgbufs = *(void **)msgbuf;
   vcos_mutex_unlock(&vchiq_lib_mutex);
   if (!msgbuf)
      msgbuf = vcos_malloc(MSGBUF_SIZE, "alloc_msgbuf");
   return msgbuf;
}