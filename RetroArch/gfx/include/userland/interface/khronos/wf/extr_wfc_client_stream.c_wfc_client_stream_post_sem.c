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
typedef  int /*<<< orphan*/  VCOS_SEMAPHORE_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_semaphore_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wfc_client_stream_post_sem(void *cb_data)
{
   VCOS_SEMAPHORE_T *sem = (VCOS_SEMAPHORE_T *)cb_data;

   vcos_log_trace("%s: sem %p", VCOS_FUNCTION, sem);
   vcos_assert(sem != NULL);
   vcos_semaphore_post(sem);
}