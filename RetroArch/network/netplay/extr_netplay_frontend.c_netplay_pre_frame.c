#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
struct timeval {int /*<<< orphan*/  member_0; } ;
struct TYPE_17__ {int /*<<< orphan*/  netplay_use_mitm_server; scalar_t__ netplay_public_announce; } ;
struct TYPE_19__ {TYPE_1__ bools; } ;
typedef  TYPE_3__ settings_t ;
struct TYPE_16__ {scalar_t__ have_inet4; scalar_t__ request_outstanding; int /*<<< orphan*/  nfds; int /*<<< orphan*/  fds; } ;
struct TYPE_20__ {int quirks; int connected_players; scalar_t__ remote_paused; scalar_t__ stall; scalar_t__ is_server; TYPE_2__* connections; TYPE_14__ nat_traversal_state; int /*<<< orphan*/  nat_traversal_task_oustanding; scalar_t__ nat_traversal; scalar_t__ local_paused; } ;
typedef  TYPE_4__ netplay_t ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_18__ {int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int NETPLAY_QUIRK_INITIALIZATION ; 
 TYPE_3__* config_get_ptr () ; 
 scalar_t__ is_mitm ; 
 int /*<<< orphan*/  natt_read (TYPE_14__*) ; 
 int /*<<< orphan*/  netplay_announce () ; 
 int /*<<< orphan*/  netplay_announce_nat_traversal (TYPE_4__*) ; 
 int /*<<< orphan*/  netplay_disconnect (TYPE_4__*) ; 
 int /*<<< orphan*/  netplay_frontend_paused (TYPE_4__*,int) ; 
 int /*<<< orphan*/  netplay_lan_ad_server (TYPE_4__*) ; 
 int /*<<< orphan*/  netplay_sync_post_frame (TYPE_4__*,int) ; 
 int /*<<< orphan*/  netplay_sync_pre_frame (TYPE_4__*) ; 
 int /*<<< orphan*/  netplay_try_init_serialization (TYPE_4__*) ; 
 int reannounce ; 
 int /*<<< orphan*/  retro_assert (TYPE_4__*) ; 
 scalar_t__ socket_select (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

bool netplay_pre_frame(netplay_t *netplay)
{
   bool sync_stalled;
   settings_t *settings  = config_get_ptr();

   retro_assert(netplay);

   if (settings->bools.netplay_public_announce)
   {
      reannounce++;
      if ((netplay->is_server || is_mitm) && (reannounce % 600 == 0))
         netplay_announce();
   }
   /* Make sure that if announcement is turned on mid-game, it gets announced */
   else
      reannounce = -1;

   /* FIXME: This is an ugly way to learn we're not paused anymore */
   if (netplay->local_paused)
      netplay_frontend_paused(netplay, false);

   /* Are we ready now? */
   if (netplay->quirks & NETPLAY_QUIRK_INITIALIZATION)
      netplay_try_init_serialization(netplay);

   if (netplay->is_server && !settings->bools.netplay_use_mitm_server)
   {
      /* Advertise our server */
      netplay_lan_ad_server(netplay);

      /* NAT traversal if applicable */
      if (netplay->nat_traversal &&
          !netplay->nat_traversal_task_oustanding &&
          netplay->nat_traversal_state.request_outstanding &&
          !netplay->nat_traversal_state.have_inet4)
      {
         struct timeval tmptv = {0};
         fd_set fds = netplay->nat_traversal_state.fds;
         if (socket_select(netplay->nat_traversal_state.nfds, &fds, NULL, NULL, &tmptv) > 0)
            natt_read(&netplay->nat_traversal_state);

#ifndef HAVE_SOCKET_LEGACY
         if (!netplay->nat_traversal_state.request_outstanding ||
             netplay->nat_traversal_state.have_inet4)
            netplay_announce_nat_traversal(netplay);
#endif
      }
   }

   sync_stalled = !netplay_sync_pre_frame(netplay);

   /* If we're disconnected, deinitialize */
   if (!netplay->is_server && !netplay->connections[0].active)
   {
      netplay_disconnect(netplay);
      return true;
   }

   if (sync_stalled ||
       ((!netplay->is_server || (netplay->connected_players>1)) &&
        (netplay->stall || netplay->remote_paused)))
   {
      /* We may have received data even if we're stalled, so run post-frame
       * sync */
      netplay_sync_post_frame(netplay, true);
      return false;
   }
   return true;
}