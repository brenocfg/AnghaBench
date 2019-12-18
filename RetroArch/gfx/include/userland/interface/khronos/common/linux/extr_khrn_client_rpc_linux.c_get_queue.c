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
typedef  int /*<<< orphan*/  VCHIU_QUEUE_T ;
struct TYPE_3__ {scalar_t__ high_priority; } ;
typedef  TYPE_1__ CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  khhn_queue ; 
 int /*<<< orphan*/  khrn_queue ; 

__attribute__((used)) static VCHIU_QUEUE_T *get_queue(CLIENT_THREAD_STATE_T *thread)
{
   return thread->high_priority ? &khhn_queue : &khrn_queue;
}