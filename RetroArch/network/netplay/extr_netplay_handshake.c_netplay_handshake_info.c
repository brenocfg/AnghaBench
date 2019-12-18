#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct retro_system_info {char* library_name; char* library_version; } ;
struct netplay_connection {int /*<<< orphan*/  mode; int /*<<< orphan*/  fd; int /*<<< orphan*/  send_packet_buffer; } ;
struct info_buf_s {void* content_crc; int /*<<< orphan*/  core_version; int /*<<< orphan*/  core_name; void** cmd; } ;
typedef  int /*<<< orphan*/  netplay_t ;
typedef  int /*<<< orphan*/  info_buf ;

/* Variables and functions */
 int NETPLAY_CMD_INFO ; 
 int /*<<< orphan*/  NETPLAY_CONNECTION_PRE_INFO ; 
 int content_get_crc () ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  memset (struct info_buf_s*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netplay_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct info_buf_s*,int) ; 
 int /*<<< orphan*/  netplay_send_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct retro_system_info* runloop_get_libretro_system_info () ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

bool netplay_handshake_info(netplay_t *netplay,
      struct netplay_connection *connection)
{
   struct info_buf_s info_buf;
   uint32_t      content_crc        = 0;
   struct retro_system_info *system = runloop_get_libretro_system_info();

   memset(&info_buf, 0, sizeof(info_buf));
   info_buf.cmd[0] = htonl(NETPLAY_CMD_INFO);
   info_buf.cmd[1] = htonl(sizeof(info_buf) - 2*sizeof(uint32_t));

   /* Get our core info */
   if (system)
   {
      strlcpy(info_buf.core_name,
            system->library_name, sizeof(info_buf.core_name));
      strlcpy(info_buf.core_version,
            system->library_version, sizeof(info_buf.core_version));
   }
   else
   {
      strlcpy(info_buf.core_name,
            "UNKNOWN", sizeof(info_buf.core_name));
      strlcpy(info_buf.core_version,
            "UNKNOWN", sizeof(info_buf.core_version));
   }

   /* Get our content CRC */
   content_crc = content_get_crc();

   if (content_crc != 0)
      info_buf.content_crc = htonl(content_crc);

   /* Send it off and wait for info back */
   if (!netplay_send(&connection->send_packet_buffer, connection->fd,
         &info_buf, sizeof(info_buf)) ||
       !netplay_send_flush(&connection->send_packet_buffer, connection->fd,
         false))
      return false;

   connection->mode = NETPLAY_CONNECTION_PRE_INFO;
   return true;
}