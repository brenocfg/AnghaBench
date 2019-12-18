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
typedef  int uint32_t ;
struct TYPE_4__ {scalar_t__ run_frame_count; scalar_t__ self_frame_count; scalar_t__ unread_frame_count; int connected_players; scalar_t__* read_frame_count; scalar_t__ server_frame_count; scalar_t__ other_frame_count; int /*<<< orphan*/  run_ptr; int /*<<< orphan*/  other_ptr; int /*<<< orphan*/  server_ptr; int /*<<< orphan*/ * read_ptr; int /*<<< orphan*/  self_ptr; } ;
typedef  TYPE_1__ netplay_t ;

/* Variables and functions */
 int MAX_CLIENTS ; 
 int /*<<< orphan*/  netplay_update_unread_ptr (TYPE_1__*) ; 

__attribute__((used)) static void netplay_force_future(netplay_t *netplay)
{
   /* Wherever we're inputting, that's where we consider our state to be loaded */
   netplay->run_ptr         = netplay->self_ptr;
   netplay->run_frame_count = netplay->self_frame_count;

   /* We need to ignore any intervening data from the other side,
    * and never rewind past this */
   netplay_update_unread_ptr(netplay);

   if (netplay->unread_frame_count < netplay->run_frame_count)
   {
      uint32_t client;
      for (client = 0; client < MAX_CLIENTS; client++)
      {
         if (!(netplay->connected_players & (1<<client)))
            continue;

         if (netplay->read_frame_count[client] < netplay->run_frame_count)
         {
            netplay->read_ptr[client] = netplay->run_ptr;
            netplay->read_frame_count[client] = netplay->run_frame_count;
         }
      }
      if (netplay->server_frame_count < netplay->run_frame_count)
      {
         netplay->server_ptr = netplay->run_ptr;
         netplay->server_frame_count = netplay->run_frame_count;
      }
      netplay_update_unread_ptr(netplay);
   }
   if (netplay->other_frame_count < netplay->run_frame_count)
   {
      netplay->other_ptr = netplay->run_ptr;
      netplay->other_frame_count = netplay->run_frame_count;
   }
}