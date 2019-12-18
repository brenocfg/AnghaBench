#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ size; int /*<<< orphan*/  data_const; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ retro_ctx_serialize_info_t ;
struct TYPE_15__ {scalar_t__ compression_backend; } ;
struct TYPE_14__ {size_t run_ptr; scalar_t__ state_size; int quirks; TYPE_5__ compress_zlib; TYPE_5__ compress_nil; scalar_t__ desync; TYPE_10__* buffer; int /*<<< orphan*/  run_frame_count; } ;
typedef  TYPE_2__ netplay_t ;
struct TYPE_12__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETPLAY_COMPRESSION_ZLIB ; 
 int NETPLAY_QUIRK_NO_SAVESTATES ; 
 int NETPLAY_QUIRK_NO_TRANSMISSION ; 
 int /*<<< orphan*/  core_serialize (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ netplay_delta_frame_ready (TYPE_2__*,TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netplay_force_future (TYPE_2__*) ; 
 int /*<<< orphan*/  netplay_send_savestate (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ,TYPE_5__*) ; 

void netplay_load_savestate(netplay_t *netplay,
      retro_ctx_serialize_info_t *serial_info, bool save)
{
   retro_ctx_serialize_info_t tmp_serial_info;

   netplay_force_future(netplay);

   /* Record it in our own buffer */
   if (save || !serial_info)
   {
      if (netplay_delta_frame_ready(netplay,
               &netplay->buffer[netplay->run_ptr], netplay->run_frame_count))
      {
         if (!serial_info)
         {
            tmp_serial_info.size = netplay->state_size;
            tmp_serial_info.data = netplay->buffer[netplay->run_ptr].state;
            if (!core_serialize(&tmp_serial_info))
               return;
            tmp_serial_info.data_const = tmp_serial_info.data;
            serial_info = &tmp_serial_info;
         }
         else
         {
            if (serial_info->size <= netplay->state_size)
               memcpy(netplay->buffer[netplay->run_ptr].state,
                     serial_info->data_const, serial_info->size);
         }
      }
      /* FIXME: This is a critical failure! */
      else
         return;
   }

   /* Don't send it if we're expected to be desynced */
   if (netplay->desync)
      return;

   /* If we can't send it to the peer, loading a state was a bad idea */
   if (netplay->quirks & (
              NETPLAY_QUIRK_NO_SAVESTATES
            | NETPLAY_QUIRK_NO_TRANSMISSION))
      return;

   /* Send this to every peer */
   if (netplay->compress_nil.compression_backend)
      netplay_send_savestate(netplay, serial_info, 0, &netplay->compress_nil);
   if (netplay->compress_zlib.compression_backend)
      netplay_send_savestate(netplay, serial_info, NETPLAY_COMPRESSION_ZLIB,
         &netplay->compress_zlib);
}