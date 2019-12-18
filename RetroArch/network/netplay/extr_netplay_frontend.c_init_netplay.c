#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct retro_callbacks {int /*<<< orphan*/  member_0; } ;
struct TYPE_11__ {int /*<<< orphan*/  netplay_start_as_spectator; int /*<<< orphan*/  netplay_use_mitm_server; scalar_t__ netplay_nat_traversal; int /*<<< orphan*/  netplay_stateless_mode; scalar_t__ netplay_public_announce; } ;
struct TYPE_10__ {scalar_t__ username; } ;
struct TYPE_9__ {int /*<<< orphan*/  netplay_check_frames; } ;
struct TYPE_12__ {TYPE_3__ bools; TYPE_2__ paths; TYPE_1__ ints; } ;
typedef  TYPE_4__ settings_t ;
struct TYPE_13__ {scalar_t__ is_server; } ;
typedef  TYPE_5__ netplay_t ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE_QUEUE_CATEGORY_INFO ; 
 int /*<<< orphan*/  MESSAGE_QUEUE_ICON_DEFAULT ; 
 int /*<<< orphan*/  MSG_CONNECTING_TO_NETPLAY_HOST ; 
 int /*<<< orphan*/  MSG_NETPLAY_FAILED ; 
 int /*<<< orphan*/  MSG_WAITING_FOR_CLIENT ; 
 int NETPLAY_QUIRK_ENDIAN_DEPENDENT ; 
 int NETPLAY_QUIRK_INITIALIZATION ; 
 int NETPLAY_QUIRK_MAP_ENDIAN_DEPENDENT ; 
 int NETPLAY_QUIRK_MAP_INITIALIZATION ; 
 int NETPLAY_QUIRK_MAP_NO_SAVESTATES ; 
 int NETPLAY_QUIRK_MAP_NO_TRANSMISSION ; 
 int NETPLAY_QUIRK_MAP_PLATFORM_DEPENDENT ; 
 scalar_t__ NETPLAY_QUIRK_MAP_UNDERSTOOD ; 
 int NETPLAY_QUIRK_NO_SAVESTATES ; 
 int NETPLAY_QUIRK_NO_TRANSMISSION ; 
 int NETPLAY_QUIRK_PLATFORM_DEPENDENT ; 
 unsigned int RARCH_DEFAULT_PORT ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RARCH_WARN (char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* config_get_ptr () ; 
 int core_serialization_quirks () ; 
 int /*<<< orphan*/  core_set_default_callbacks (struct retro_callbacks*) ; 
 int /*<<< orphan*/  core_set_netplay_callbacks () ; 
 scalar_t__ discord_get_own_username () ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netplay_announce () ; 
 int /*<<< orphan*/  netplay_client_deferred ; 
 TYPE_5__* netplay_data ; 
 int netplay_enabled ; 
 int netplay_is_client ; 
 scalar_t__ netplay_new (void*,char const*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct retro_callbacks*,int,scalar_t__,int) ; 
 int /*<<< orphan*/  netplay_toggle_play_spectate (TYPE_5__*) ; 
 int /*<<< orphan*/  runloop_msg_queue_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char const* server_address_deferred ; 
 unsigned int server_port_deferred ; 

bool init_netplay(void *direct_host, const char *server, unsigned port)
{
   struct retro_callbacks cbs    = {0};
   settings_t *settings          = config_get_ptr();
   uint64_t serialization_quirks = 0;
   uint64_t quirks               = 0;
   bool _netplay_is_client       = netplay_is_client;
   bool _netplay_enabled         = netplay_enabled;

   if (!_netplay_enabled)
      return false;

   core_set_default_callbacks(&cbs);
   if (!core_set_netplay_callbacks())
      return false;

   /* Map the core's quirks to our quirks */
   serialization_quirks = core_serialization_quirks();
   if (serialization_quirks & ~((uint64_t) NETPLAY_QUIRK_MAP_UNDERSTOOD))
   {
      /* Quirks we don't support! Just disable everything. */
      quirks |= NETPLAY_QUIRK_NO_SAVESTATES;
   }
   if (serialization_quirks & NETPLAY_QUIRK_MAP_NO_SAVESTATES)
      quirks |= NETPLAY_QUIRK_NO_SAVESTATES;
   if (serialization_quirks & NETPLAY_QUIRK_MAP_NO_TRANSMISSION)
      quirks |= NETPLAY_QUIRK_NO_TRANSMISSION;
   if (serialization_quirks & NETPLAY_QUIRK_MAP_INITIALIZATION)
      quirks |= NETPLAY_QUIRK_INITIALIZATION;
   if (serialization_quirks & NETPLAY_QUIRK_MAP_ENDIAN_DEPENDENT)
      quirks |= NETPLAY_QUIRK_ENDIAN_DEPENDENT;
   if (serialization_quirks & NETPLAY_QUIRK_MAP_PLATFORM_DEPENDENT)
      quirks |= NETPLAY_QUIRK_PLATFORM_DEPENDENT;

   if (_netplay_is_client)
   {
      RARCH_LOG("[netplay] %s\n", msg_hash_to_str(MSG_CONNECTING_TO_NETPLAY_HOST));
   }
   else
   {
      RARCH_LOG("[netplay] %s\n", msg_hash_to_str(MSG_WAITING_FOR_CLIENT));
      runloop_msg_queue_push(
         msg_hash_to_str(MSG_WAITING_FOR_CLIENT),
         0, 180, false,
         NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);

      if (settings->bools.netplay_public_announce)
         netplay_announce();
   }

   netplay_data = (netplay_t*)netplay_new(
         _netplay_is_client ? direct_host : NULL,
         _netplay_is_client ? (!netplay_client_deferred ? server
            : server_address_deferred) : NULL,
         _netplay_is_client ? (!netplay_client_deferred ? port
            : server_port_deferred   ) : (port != 0 ? port : RARCH_DEFAULT_PORT),
         settings->bools.netplay_stateless_mode,
         settings->ints.netplay_check_frames,
         &cbs,
         settings->bools.netplay_nat_traversal && !settings->bools.netplay_use_mitm_server,
#ifdef HAVE_DISCORD
         discord_get_own_username() ? discord_get_own_username() :
#endif
         settings->paths.username,
         quirks);

   if (netplay_data)
   {
      if (netplay_data->is_server && !settings->bools.netplay_start_as_spectator)
         netplay_toggle_play_spectate(netplay_data);
      return true;
   }

   RARCH_WARN("%s\n", msg_hash_to_str(MSG_NETPLAY_FAILED));

   runloop_msg_queue_push(
         msg_hash_to_str(MSG_NETPLAY_FAILED),
         0, 180, false,
         NULL, MESSAGE_QUEUE_ICON_DEFAULT, MESSAGE_QUEUE_CATEGORY_INFO);
   return false;
}