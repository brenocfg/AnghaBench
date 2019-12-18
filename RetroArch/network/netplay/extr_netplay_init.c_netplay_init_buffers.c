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
struct delta_frame {int dummy; } ;
struct TYPE_5__ {int buffer_size; int quirks; struct delta_frame* buffer; scalar_t__ is_server; } ;
typedef  TYPE_1__ netplay_t ;

/* Variables and functions */
 int NETPLAY_MAX_STALL_FRAMES ; 
 int NETPLAY_QUIRK_INITIALIZATION ; 
 int NETPLAY_QUIRK_NO_SAVESTATES ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  netplay_init_serialization (TYPE_1__*) ; 
 int netplay_init_socket_buffers (TYPE_1__*) ; 

__attribute__((used)) static bool netplay_init_buffers(netplay_t *netplay)
{
   struct delta_frame *delta_frames = NULL;

   /* Enough to get ahead or behind by MAX_STALL_FRAMES frames, plus one for
    * other remote clients, plus one to send the stall message */
   netplay->buffer_size = NETPLAY_MAX_STALL_FRAMES + 2;

   /* If we're the server, we need enough to get ahead AND behind by
    * MAX_STALL_FRAMES frame */
   if (netplay->is_server)
      netplay->buffer_size *= 2;

   delta_frames = (struct delta_frame*)calloc(netplay->buffer_size,
         sizeof(*delta_frames));

   if (!delta_frames)
      return false;

   netplay->buffer = delta_frames;

   if (!(netplay->quirks & (NETPLAY_QUIRK_NO_SAVESTATES|NETPLAY_QUIRK_INITIALIZATION)))
      netplay_init_serialization(netplay);

   return netplay_init_socket_buffers(netplay);
}