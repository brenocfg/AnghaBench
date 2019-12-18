#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct string_list {unsigned int size; TYPE_1__* elems; } ;
struct retro_system_info {char* library_name; char* library_version; } ;
struct TYPE_12__ {int netplay_use_mitm_server; } ;
struct TYPE_11__ {char* username; scalar_t__* netplay_spectate_password; scalar_t__* netplay_password; } ;
struct TYPE_10__ {char* netplay_mitm_server; } ;
struct TYPE_9__ {int netplay_port; } ;
struct TYPE_13__ {TYPE_5__ bools; TYPE_4__ paths; TYPE_3__ arrays; TYPE_2__ uints; } ;
typedef  TYPE_6__ settings_t ;
typedef  int /*<<< orphan*/  frontend_architecture ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_8__ {char* data; } ;

/* Variables and functions */
 char* PACKAGE_VERSION ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char*) ; 
 int /*<<< orphan*/  RARCH_PATH_BASENAME ; 
 int /*<<< orphan*/  RARCH_PATH_SUBSYSTEM ; 
 TYPE_6__* config_get_ptr () ; 
 int content_get_crc () ; 
 char* discord_get_own_username () ; 
 scalar_t__ discord_is_ready () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  net_http_urlencode (char**,char*) ; 
 int /*<<< orphan*/  netplay_announce_cb ; 
 int /*<<< orphan*/  netplay_get_architecture (char*,int) ; 
 char* path_basename (char*) ; 
 char* path_get (int /*<<< orphan*/ ) ; 
 struct string_list* path_get_subsystem_list () ; 
 struct retro_system_info* runloop_get_libretro_system_info () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*,char*,int,int,char*,int,int,int,char*,char*,char*) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  task_push_http_post_transfer (char*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void netplay_announce(void)
{
   char buf[4600];
   char frontend_architecture[PATH_MAX_LENGTH];
   char url[2048]                   = "http://lobby.libretro.com/add/";
   char *username                   = NULL;
   char *corename                   = NULL;
   char *gamename                   = NULL;
   char *subsystemname              = NULL;
   char *coreversion                = NULL;
   char *frontend_ident             = NULL;
   settings_t *settings             = config_get_ptr();
   struct retro_system_info *system = runloop_get_libretro_system_info();
   uint32_t content_crc             = content_get_crc();
   struct string_list *subsystem    = path_get_subsystem_list();

   buf[0] = '\0';

   if (subsystem)
   {
      unsigned i;

      for (i = 0; i < subsystem->size; i++)
      {
         strlcat(buf, path_basename(subsystem->elems[i].data), sizeof(buf));
         if (i < subsystem->size - 1)
            strlcat(buf, "|", sizeof(buf));
      }
      net_http_urlencode(&gamename, buf);
      net_http_urlencode(&subsystemname, path_get(RARCH_PATH_SUBSYSTEM));
      content_crc = 0;
   }
   else
   {
      net_http_urlencode(&gamename,
         !string_is_empty(path_basename(path_get(RARCH_PATH_BASENAME))) ?
         path_basename(path_get(RARCH_PATH_BASENAME)) : "N/A");
      net_http_urlencode(&subsystemname, "N/A");
   }

   netplay_get_architecture(frontend_architecture, sizeof(frontend_architecture));

#ifdef HAVE_DISCORD
   if(discord_is_ready())
      net_http_urlencode(&username, discord_get_own_username());
   else
#endif
   net_http_urlencode(&username, settings->paths.username);
   net_http_urlencode(&corename, system->library_name);
   net_http_urlencode(&coreversion, system->library_version);
   net_http_urlencode(&frontend_ident, frontend_architecture);

   buf[0] = '\0';

   snprintf(buf, sizeof(buf), "username=%s&core_name=%s&core_version=%s&"
      "game_name=%s&game_crc=%08X&port=%d&mitm_server=%s"
      "&has_password=%d&has_spectate_password=%d&force_mitm=%d"
      "&retroarch_version=%s&frontend=%s&subsystem_name=%s",
      username, corename, coreversion, gamename, content_crc,
      settings->uints.netplay_port,
      settings->arrays.netplay_mitm_server,
      *settings->paths.netplay_password ? 1 : 0,
      *settings->paths.netplay_spectate_password ? 1 : 0,
      settings->bools.netplay_use_mitm_server,
      PACKAGE_VERSION, frontend_architecture, subsystemname);
#if 0
   RARCH_LOG("[netplay] announcement URL: %s\n", buf);
#endif
   task_push_http_post_transfer(url, buf, true, NULL, netplay_announce_cb, NULL);

   if (username)
      free(username);
   if (corename)
      free(corename);
   if (gamename)
      free(gamename);
   if (coreversion)
      free(coreversion);
   if (frontend_ident)
      free(frontend_ident);
}