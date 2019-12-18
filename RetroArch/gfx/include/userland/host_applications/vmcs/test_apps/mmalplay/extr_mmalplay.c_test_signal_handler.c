#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ ctx; } ;
typedef  int MMAL_BOOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*) ; 
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  mmalplay_stop (scalar_t__) ; 
 TYPE_1__* play_info ; 
 int play_info_count ; 
 int /*<<< orphan*/  vcos_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_mutex_unlock (int /*<<< orphan*/ *) ; 

void test_signal_handler(int signum)
{
   static MMAL_BOOL_T stopped_already = 0;
   int i;
   MMAL_PARAM_UNUSED(signum);

   if (stopped_already)
   {
      LOG_ERROR("Killing program");
      exit(255);
   }
   stopped_already = 1;

   LOG_ERROR("BYE");
   for (i = 0; i < play_info_count; i++)
   {
      vcos_mutex_lock(&play_info[i].lock);
      if (play_info[i].ctx)
         mmalplay_stop(play_info[i].ctx);
      vcos_mutex_unlock(&play_info[i].lock);
   }
}