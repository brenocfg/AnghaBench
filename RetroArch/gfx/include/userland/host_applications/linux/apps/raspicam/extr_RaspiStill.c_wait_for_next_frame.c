#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int int64_t ;
struct TYPE_4__ {int /*<<< orphan*/  verbose; } ;
struct TYPE_5__ {int timeout; int frameNextMethod; int timelapse; TYPE_1__ common_settings; } ;
typedef  TYPE_2__ RASPISTILL_STATE ;

/* Variables and functions */
 int CAMERA_SETTLE_TIME ; 
#define  FRAME_NEXT_FOREVER 134 
#define  FRAME_NEXT_GPIO 133 
#define  FRAME_NEXT_IMMEDIATELY 132 
#define  FRAME_NEXT_KEYPRESS 131 
#define  FRAME_NEXT_SIGNAL 130 
#define  FRAME_NEXT_SINGLE 129 
#define  FRAME_NEXT_TIMELAPSE 128 
 int SIGUSR1 ; 
 int SIGUSR2 ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int get_microseconds64 () ; 
 int getchar () ; 
 int /*<<< orphan*/  pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int sigwait (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  vcos_log_error (char*,int,int) ; 
 int /*<<< orphan*/  vcos_sleep (int) ; 

__attribute__((used)) static int wait_for_next_frame(RASPISTILL_STATE *state, int *frame)
{
   static int64_t complete_time = -1;
   int keep_running = 1;

   int64_t current_time =  get_microseconds64()/1000;

   if (complete_time == -1)
      complete_time =  current_time + state->timeout;

   // if we have run out of time, flag we need to exit
   // If timeout = 0 then always continue
   if (current_time >= complete_time && state->timeout != 0)
      keep_running = 0;

   switch (state->frameNextMethod)
   {
   case FRAME_NEXT_SINGLE :
      // simple timeout for a single capture
      vcos_sleep(state->timeout);
      return 0;

   case FRAME_NEXT_FOREVER :
   {
      *frame+=1;

      // Have a sleep so we don't hog the CPU.
      vcos_sleep(10000);

      // Run forever so never indicate end of loop
      return 1;
   }

   case FRAME_NEXT_TIMELAPSE :
   {
      static int64_t next_frame_ms = -1;

      // Always need to increment by at least one, may add a skip later
      *frame += 1;

      if (next_frame_ms == -1)
      {
         vcos_sleep(CAMERA_SETTLE_TIME);

         // Update our current time after the sleep
         current_time =  get_microseconds64()/1000;

         // Set our initial 'next frame time'
         next_frame_ms = current_time + state->timelapse;
      }
      else
      {
         int64_t this_delay_ms = next_frame_ms - current_time;

         if (this_delay_ms < 0)
         {
            // We are already past the next exposure time
            if (-this_delay_ms < state->timelapse/2)
            {
               // Less than a half frame late, take a frame and hope to catch up next time
               next_frame_ms += state->timelapse;
               vcos_log_error("Frame %d is %d ms late", *frame, (int)(-this_delay_ms));
            }
            else
            {
               int nskip = 1 + (-this_delay_ms)/state->timelapse;
               vcos_log_error("Skipping frame %d to restart at frame %d", *frame, *frame+nskip);
               *frame += nskip;
               this_delay_ms += nskip * state->timelapse;
               vcos_sleep(this_delay_ms);
               next_frame_ms += (nskip + 1) * state->timelapse;
            }
         }
         else
         {
            vcos_sleep(this_delay_ms);
            next_frame_ms += state->timelapse;
         }
      }

      return keep_running;
   }

   case FRAME_NEXT_KEYPRESS :
   {
      int ch;

      if (state->common_settings.verbose)
         fprintf(stderr, "Press Enter to capture, X then ENTER to exit\n");

      ch = getchar();
      *frame+=1;
      if (ch == 'x' || ch == 'X')
         return 0;
      else
      {
         return keep_running;
      }
   }

   case FRAME_NEXT_IMMEDIATELY :
   {
      // Not waiting, just go to next frame.
      // Actually, we do need a slight delay here otherwise exposure goes
      // badly wrong since we never allow it frames to work it out
      // This could probably be tuned down.
      // First frame has a much longer delay to ensure we get exposure to a steady state
      if (*frame == 0)
         vcos_sleep(CAMERA_SETTLE_TIME);
      else
         vcos_sleep(30);

      *frame+=1;

      return keep_running;
   }

   case FRAME_NEXT_GPIO :
   {
      // Intended for GPIO firing of a capture
      return 0;
   }

   case FRAME_NEXT_SIGNAL :
   {
      // Need to wait for a SIGUSR1 or SIGUSR2 signal
      sigset_t waitset;
      int sig;
      int result = 0;

      sigemptyset( &waitset );
      sigaddset( &waitset, SIGUSR1 );
      sigaddset( &waitset, SIGUSR2 );

      // We are multi threaded because we use mmal, so need to use the pthread
      // variant of procmask to block until a SIGUSR1 or SIGUSR2 signal appears
      pthread_sigmask( SIG_BLOCK, &waitset, NULL );

      if (state->common_settings.verbose)
      {
         fprintf(stderr, "Waiting for SIGUSR1 to initiate capture and continue or SIGUSR2 to capture and exit\n");
      }

      result = sigwait( &waitset, &sig );

      if (result == 0)
      {
         if (sig == SIGUSR1)
         {
            if (state->common_settings.verbose)
               fprintf(stderr, "Received SIGUSR1\n");
         }
         else if (sig == SIGUSR2)
         {
            if (state->common_settings.verbose)
               fprintf(stderr, "Received SIGUSR2\n");
            keep_running = 0;
         }
      }
      else
      {
         if (state->common_settings.verbose)
            fprintf(stderr, "Bad signal received - error %d\n", errno);
      }

      *frame+=1;

      return keep_running;
   }
   } // end of switch

   // Should have returned by now, but default to timeout
   return keep_running;
}