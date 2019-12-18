#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct netplay_connection {int stall; scalar_t__ mode; scalar_t__ stall_time; scalar_t__ active; int /*<<< orphan*/  stall_frame; } ;
struct TYPE_14__ {int netplay_input_latency_frames_min; int run_ahead_frames; int netplay_input_latency_frames_range; } ;
struct TYPE_13__ {scalar_t__ run_ahead_enabled; } ;
struct TYPE_15__ {TYPE_2__ uints; TYPE_1__ bools; } ;
typedef  TYPE_3__ settings_t ;
typedef  scalar_t__ retro_time_t ;
struct TYPE_16__ {int can_poll; scalar_t__ self_mode; int connected_players; scalar_t__ unread_frame_count; scalar_t__ run_frame_count; int frame_run_time_avg; int input_latency_frames; int stall; scalar_t__ self_frame_count; size_t connections_size; scalar_t__ stall_time; scalar_t__* read_frame_count; struct netplay_connection* connections; scalar_t__ is_server; scalar_t__ remote_paused; scalar_t__ stateless_mode; scalar_t__ connected_slaves; int /*<<< orphan*/  run_ptr; } ;
typedef  TYPE_4__ netplay_t ;

/* Variables and functions */
 int MAX_CLIENTS ; 
 scalar_t__ MAX_CLIENT_STALL_TIME_USEC ; 
 scalar_t__ MAX_SERVER_STALL_TIME_USEC ; 
 scalar_t__ NETPLAY_CONNECTION_NONE ; 
 scalar_t__ NETPLAY_CONNECTION_PLAYING ; 
 scalar_t__ NETPLAY_CONNECTION_SLAVE ; 
 scalar_t__ NETPLAY_CONNECTION_SPECTATING ; 
 scalar_t__ NETPLAY_MAX_STALL_FRAMES ; 
#define  NETPLAY_STALL_INPUT_LATENCY 132 
 void* NETPLAY_STALL_NONE ; 
#define  NETPLAY_STALL_NO_CONNECTION 131 
#define  NETPLAY_STALL_RUNNING_FAST 130 
#define  NETPLAY_STALL_SERVER_REQUESTED 129 
#define  NETPLAY_STALL_SPECTATOR_WAIT 128 
 TYPE_3__* config_get_ptr () ; 
 scalar_t__ cpu_features_get_time_usec () ; 
 int /*<<< orphan*/  get_self_input_state (TYPE_4__*) ; 
 int /*<<< orphan*/  netplay_handle_slaves (TYPE_4__*) ; 
 int /*<<< orphan*/  netplay_hangup (TYPE_4__*,struct netplay_connection*) ; 
 int netplay_poll_net_input (TYPE_4__*,int) ; 
 int /*<<< orphan*/  netplay_resolve_input (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netplay_update_unread_ptr (TYPE_4__*) ; 

__attribute__((used)) static bool netplay_poll(netplay_t *netplay)
{
   int res;
   uint32_t client;
   size_t i;

   netplay->can_poll = false;

   if (!get_self_input_state(netplay))
      goto catastrophe;

   /* If we're not connected, we're done */
   if (netplay->self_mode == NETPLAY_CONNECTION_NONE)
      return true;

   /* Read Netplay input, block if we're configured to stall for input every
    * frame */
   netplay_update_unread_ptr(netplay);
   if (netplay->stateless_mode &&
       (netplay->connected_players>1) &&
       netplay->unread_frame_count <= netplay->run_frame_count)
      res = netplay_poll_net_input(netplay, true);
   else
      res = netplay_poll_net_input(netplay, false);
   if (res == -1)
      goto catastrophe;

   /* Resolve and/or simulate the input if we don't have real input */
   netplay_resolve_input(netplay, netplay->run_ptr, false);

   /* Handle any slaves */
   if (netplay->is_server && netplay->connected_slaves)
      netplay_handle_slaves(netplay);

   netplay_update_unread_ptr(netplay);

   /* Figure out how many frames of input latency we should be using to hide
    * network latency */
   if (netplay->frame_run_time_avg || netplay->stateless_mode)
   {
      /* FIXME: Using fixed 60fps for this calculation */
      unsigned frames_per_frame    = netplay->frame_run_time_avg ?
         (16666 / netplay->frame_run_time_avg) :
         0;
      unsigned frames_ahead        = (netplay->run_frame_count > netplay->unread_frame_count) ?
         (netplay->run_frame_count - netplay->unread_frame_count) :
         0;
      settings_t *settings         = config_get_ptr();
      int input_latency_frames_min = settings->uints.netplay_input_latency_frames_min -
            (settings->bools.run_ahead_enabled ? settings->uints.run_ahead_frames : 0);
      int input_latency_frames_max = input_latency_frames_min + settings->uints.netplay_input_latency_frames_range;

      /* Assume we need a couple frames worth of time to actually run the
       * current frame */
      if (frames_per_frame > 2)
         frames_per_frame -= 2;
      else
         frames_per_frame = 0;

      /* Shall we adjust our latency? */
      if (netplay->stateless_mode)
      {
         /* In stateless mode, we adjust up if we're "close" and down if we
          * have a lot of slack */
         if (netplay->input_latency_frames < input_latency_frames_min ||
               (netplay->unread_frame_count == netplay->run_frame_count + 1 &&
                netplay->input_latency_frames < input_latency_frames_max))
            netplay->input_latency_frames++;
         else if (netplay->input_latency_frames > input_latency_frames_max ||
               (netplay->unread_frame_count > netplay->run_frame_count + 2 &&
                netplay->input_latency_frames > input_latency_frames_min))
            netplay->input_latency_frames--;
      }
      else if (netplay->input_latency_frames < input_latency_frames_min ||
               (frames_per_frame < frames_ahead &&
                netplay->input_latency_frames < input_latency_frames_max))
      {
         /* We can't hide this much network latency with replay, so hide some
          * with input latency */
         netplay->input_latency_frames++;
      }
      else if (netplay->input_latency_frames > input_latency_frames_max ||
               (frames_per_frame > frames_ahead + 2 &&
                netplay->input_latency_frames > input_latency_frames_min))
      {
         /* We don't need this much latency (any more) */
         netplay->input_latency_frames--;
      }
   }

   /* If we're stalled, consider unstalling */
   switch (netplay->stall)
   {
      case NETPLAY_STALL_RUNNING_FAST:
         {
            if (netplay->unread_frame_count + NETPLAY_MAX_STALL_FRAMES - 2
                  > netplay->self_frame_count)
            {
               netplay->stall = NETPLAY_STALL_NONE;
               for (i = 0; i < netplay->connections_size; i++)
               {
                  struct netplay_connection *connection = &netplay->connections[i];
                  if (connection->active && connection->stall)
                     connection->stall = NETPLAY_STALL_NONE;
               }
            }
            break;
         }

      case NETPLAY_STALL_SPECTATOR_WAIT:
         if (netplay->self_mode == NETPLAY_CONNECTION_PLAYING || netplay->unread_frame_count > netplay->self_frame_count)
            netplay->stall = NETPLAY_STALL_NONE;
         break;

      case NETPLAY_STALL_INPUT_LATENCY:
         /* Just let it recalculate momentarily */
         netplay->stall = NETPLAY_STALL_NONE;
         break;

      case NETPLAY_STALL_SERVER_REQUESTED:
         /* See if the stall is done */
         if (netplay->connections[0].stall_frame == 0)
         {
            /* Stop stalling! */
            netplay->connections[0].stall = NETPLAY_STALL_NONE;
            netplay->stall = NETPLAY_STALL_NONE;
         }
         else
            netplay->connections[0].stall_frame--;
         break;
      case NETPLAY_STALL_NO_CONNECTION:
         /* We certainly haven't fixed this */
         break;
      default: /* not stalling */
         break;
   }

   /* If we're not stalled, consider stalling */
   if (!netplay->stall)
   {
      /* Have we not read enough latency frames? */
      if (netplay->self_mode == NETPLAY_CONNECTION_PLAYING &&
          netplay->connected_players &&
          netplay->run_frame_count + netplay->input_latency_frames > netplay->self_frame_count)
      {
         netplay->stall = NETPLAY_STALL_INPUT_LATENCY;
         netplay->stall_time = 0;
      }

      /* Are we too far ahead? */
      if (netplay->unread_frame_count + NETPLAY_MAX_STALL_FRAMES
            <= netplay->self_frame_count)
      {
         netplay->stall      = NETPLAY_STALL_RUNNING_FAST;
         netplay->stall_time = cpu_features_get_time_usec();

         /* Figure out who to blame */
         if (netplay->is_server)
         {
            for (client = 1; client < MAX_CLIENTS; client++)
            {
               struct netplay_connection *connection;
               if (!(netplay->connected_players & (1<<client)))
                  continue;
               if (netplay->read_frame_count[client] > netplay->unread_frame_count)
                  continue;
               connection = &netplay->connections[client-1];
               if (connection->active &&
                   connection->mode == NETPLAY_CONNECTION_PLAYING)
               {
                  connection->stall = NETPLAY_STALL_RUNNING_FAST;
                  connection->stall_time = netplay->stall_time;
               }
            }
         }

      }

      /* If we're a spectator, are we ahead at all? */
      if (!netplay->is_server &&
          (netplay->self_mode == NETPLAY_CONNECTION_SPECTATING ||
           netplay->self_mode == NETPLAY_CONNECTION_SLAVE) &&
          netplay->unread_frame_count <= netplay->self_frame_count)
      {
         netplay->stall = NETPLAY_STALL_SPECTATOR_WAIT;
         netplay->stall_time = cpu_features_get_time_usec();
      }
   }

   /* If we're stalling, consider disconnection */
   if (netplay->stall && netplay->stall_time)
   {
      retro_time_t now = cpu_features_get_time_usec();

      /* Don't stall out while they're paused */
      if (netplay->remote_paused)
         netplay->stall_time = now;
      else if (now - netplay->stall_time >=
               (netplay->is_server ? MAX_SERVER_STALL_TIME_USEC :
                                          MAX_CLIENT_STALL_TIME_USEC))
      {
         /* Stalled out! */
         if (netplay->is_server)
         {
            bool fixed = false;
            for (i = 0; i < netplay->connections_size; i++)
            {
               struct netplay_connection *connection = &netplay->connections[i];
               if (connection->active &&
                   connection->mode == NETPLAY_CONNECTION_PLAYING &&
                   connection->stall)
               {
                  netplay_hangup(netplay, connection);
                  fixed = true;
               }
            }

            if (fixed)
            {
               /* Not stalled now :) */
               netplay->stall = NETPLAY_STALL_NONE;
               return true;
            }
         }
         else
            goto catastrophe;
         return false;
      }
   }

   return true;

catastrophe:
   for (i = 0; i < netplay->connections_size; i++)
      netplay_hangup(netplay, &netplay->connections[i]);
   return false;
}