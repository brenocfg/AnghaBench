#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct netplay_host_list {int /*<<< orphan*/  size; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  member_0; } ;
struct ad_packet {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_7__ {TYPE_1__* entries; int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ net_ifinfo_t ;
typedef  enum rarch_netplay_discovery_ctl_state { ____Placeholder_rarch_netplay_discovery_ctl_state } rarch_netplay_discovery_ctl_state ;
typedef  int /*<<< orphan*/  canBroadcast ;
struct TYPE_8__ {int /*<<< orphan*/  address; int /*<<< orphan*/  protocol_version; } ;
struct TYPE_6__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETPLAY_HOST_STR_LEN ; 
 int /*<<< orphan*/  NETPLAY_PROTOCOL_VERSION ; 
 scalar_t__ RARCH_DEFAULT_PORT ; 
#define  RARCH_NETPLAY_DISCOVERY_CTL_LAN_CLEAR_RESPONSES 130 
#define  RARCH_NETPLAY_DISCOVERY_CTL_LAN_GET_RESPONSES 129 
#define  RARCH_NETPLAY_DISCOVERY_CTL_LAN_SEND_QUERY 128 
 int /*<<< orphan*/  RARCH_WARN (char*,...) ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_BROADCAST ; 
 TYPE_5__ ad_packet_buffer ; 
 struct netplay_host_list discovered_hosts ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  freeaddrinfo_retro (struct addrinfo*) ; 
 int /*<<< orphan*/  getaddrinfo_retro (char*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ lan_ad_client_fd ; 
 int /*<<< orphan*/  memcpy (void*,char*,int) ; 
 int /*<<< orphan*/  net_ifinfo_free (TYPE_2__*) ; 
 int /*<<< orphan*/  net_ifinfo_new (TYPE_2__*) ; 
 int /*<<< orphan*/  netplay_lan_ad_client () ; 
 scalar_t__ sendto (scalar_t__,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsockopt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned short) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool netplay_discovery_driver_ctl(enum rarch_netplay_discovery_ctl_state state, void *data)
{
#ifdef HAVE_NETPLAYDISCOVERY
   char port_str[6];
   int ret;
   unsigned k = 0;

   if (lan_ad_client_fd < 0)
      return false;

   switch (state)
   {
      case RARCH_NETPLAY_DISCOVERY_CTL_LAN_SEND_QUERY:
      {
         net_ifinfo_t interfaces;
         struct addrinfo hints = {0}, *addr;
         int canBroadcast      = 1;

         if (!net_ifinfo_new(&interfaces))
            return false;

         /* Get the broadcast address (IPv4 only for now) */
         snprintf(port_str, 6, "%hu", (unsigned short) RARCH_DEFAULT_PORT);
         if (getaddrinfo_retro("255.255.255.255", port_str, &hints, &addr) < 0)
            return false;

         /* Make it broadcastable */
#if defined(SOL_SOCKET) && defined(SO_BROADCAST)
         if (setsockopt(lan_ad_client_fd, SOL_SOCKET, SO_BROADCAST,
                  (const char *)&canBroadcast, sizeof(canBroadcast)) < 0)
            RARCH_WARN("[discovery] Failed to set netplay discovery port to broadcast\n");
#endif

         /* Put together the request */
         memcpy((void *) &ad_packet_buffer, "RANQ", 4);
         ad_packet_buffer.protocol_version = htonl(NETPLAY_PROTOCOL_VERSION);

         for (k = 0; k < (unsigned)interfaces.size; k++)
         {
            strlcpy(ad_packet_buffer.address, interfaces.entries[k].host,
               NETPLAY_HOST_STR_LEN);

            /* And send it off */
            ret = (int)sendto(lan_ad_client_fd, (const char *) &ad_packet_buffer,
               sizeof(struct ad_packet), 0, addr->ai_addr, addr->ai_addrlen);
            if (ret < (ssize_t) (2*sizeof(uint32_t)))
               RARCH_WARN("[discovery] Failed to send netplay discovery query (error: %d)\n", errno);
         }

         freeaddrinfo_retro(addr);
         net_ifinfo_free(&interfaces);

         break;
      }

      case RARCH_NETPLAY_DISCOVERY_CTL_LAN_GET_RESPONSES:
         if (!netplay_lan_ad_client())
            return false;
         *((struct netplay_host_list **) data) = &discovered_hosts;
         break;

      case RARCH_NETPLAY_DISCOVERY_CTL_LAN_CLEAR_RESPONSES:
         discovered_hosts.size = 0;
         break;

      default:
         return false;
   }
#endif
   return true;
}