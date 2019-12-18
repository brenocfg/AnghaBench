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
typedef  scalar_t__ vc_container_net_status_t ;
typedef  int vc_container_net_open_flags_t ;
struct addrinfo {int type; int /*<<< orphan*/  read_timeout_ms; int /*<<< orphan*/  max_datagram_size; scalar_t__ socket; int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  to_addr; int /*<<< orphan*/  to_addr_len; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; } ;
typedef  int /*<<< orphan*/  hints ;
typedef  struct addrinfo VC_CONTAINER_NET_T ;
typedef  scalar_t__ SOCKET_T ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  AF_UNSPEC ; 
#define  DATAGRAM_RECEIVER 133 
#define  DATAGRAM_SENDER 132 
 int /*<<< orphan*/  INFINITE_TIMEOUT_MS ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  SOCKET_ERROR ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
#define  STREAM_CLIENT 131 
#define  STREAM_SERVER 130 
 scalar_t__ VC_CONTAINER_NET_ERROR_INVALID_PARAMETER ; 
 scalar_t__ VC_CONTAINER_NET_ERROR_NO_MEMORY ; 
#define  VC_CONTAINER_NET_OPEN_FLAG_FORCE_IP4 129 
#define  VC_CONTAINER_NET_OPEN_FLAG_FORCE_IP6 128 
 int VC_CONTAINER_NET_OPEN_FLAG_FORCE_MASK ; 
 int VC_CONTAINER_NET_OPEN_FLAG_STREAM ; 
 scalar_t__ VC_CONTAINER_NET_SUCCESS ; 
 int /*<<< orphan*/  bind (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connect (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int getaddrinfo (char const*,char const*,struct addrinfo*,struct addrinfo**) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_clear_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_container_net_close (struct addrinfo*) ; 
 int /*<<< orphan*/  vc_container_net_private_close (scalar_t__) ; 
 int /*<<< orphan*/  vc_container_net_private_deinit () ; 
 scalar_t__ vc_container_net_private_init () ; 
 scalar_t__ vc_container_net_private_last_error () ; 
 int /*<<< orphan*/  vc_container_net_private_maximum_datagram_size (scalar_t__) ; 
 int /*<<< orphan*/  vc_container_net_private_set_reusable (scalar_t__,int) ; 

VC_CONTAINER_NET_T *vc_container_net_open( const char *address, const char *port,
      vc_container_net_open_flags_t flags, vc_container_net_status_t *p_status )
{
   VC_CONTAINER_NET_T *p_ctx;
   struct addrinfo hints, *info, *p;
   int result;
   vc_container_net_status_t status;
   SOCKET_T sock = INVALID_SOCKET;

   status = vc_container_net_private_init();
   if (status != VC_CONTAINER_NET_SUCCESS)
   {
      LOG_ERROR(NULL, "vc_container_net_open: platform initialization failure: %d", status);
      if (p_status)
         *p_status = status;
      return NULL;
   }

   p_ctx = (VC_CONTAINER_NET_T *)malloc(sizeof(VC_CONTAINER_NET_T));
   if (!p_ctx)
   {
      if (p_status)
         *p_status = VC_CONTAINER_NET_ERROR_NO_MEMORY;

      LOG_ERROR(NULL, "vc_container_net_open: malloc fail for VC_CONTAINER_NET_T");
      vc_container_net_private_deinit();
      return NULL;
   }

   /* Initialize the net socket instance structure */
   memset(p_ctx, 0, sizeof(*p_ctx));
   p_ctx->socket = INVALID_SOCKET;
   if (flags & VC_CONTAINER_NET_OPEN_FLAG_STREAM)
      p_ctx->type = address ? STREAM_CLIENT : STREAM_SERVER;
   else
      p_ctx->type = address ? DATAGRAM_SENDER : DATAGRAM_RECEIVER;

   /* Create the address info linked list from the data provided */
   memset(&hints, 0, sizeof(hints));
   switch (flags & VC_CONTAINER_NET_OPEN_FLAG_FORCE_MASK)
   {
   case 0:
      hints.ai_family = AF_UNSPEC;
      break;
   case VC_CONTAINER_NET_OPEN_FLAG_FORCE_IP4:
      hints.ai_family = AF_INET;
      break;
   case VC_CONTAINER_NET_OPEN_FLAG_FORCE_IP6:
      hints.ai_family = AF_INET6;
      break;
   default:
      status = VC_CONTAINER_NET_ERROR_INVALID_PARAMETER;
      LOG_ERROR(NULL, "vc_container_net_open: invalid address forcing flag");
      goto error;
   }
   hints.ai_socktype = (flags & VC_CONTAINER_NET_OPEN_FLAG_STREAM) ? SOCK_STREAM : SOCK_DGRAM;

   result = getaddrinfo(address, port, &hints, &info);
   if (result)
   {
      status = vc_container_net_private_last_error();
      LOG_ERROR(NULL, "vc_container_net_open: unable to get address info: %d", status);
      goto error;
   }

   /* Not all address infos may be useable. Search for one that is by skipping any
    * that provoke errors. */
   for(p = info; (p != NULL) && (sock == INVALID_SOCKET) ; p = p->ai_next)
   {
      sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
      if (sock == INVALID_SOCKET)
      {
         status = vc_container_net_private_last_error();
         continue;
      }

      switch (p_ctx->type)
      {
      case STREAM_CLIENT:
            /* Simply connect to the given address/port */
            if (connect(sock, p->ai_addr, p->ai_addrlen) == SOCKET_ERROR)
               status = vc_container_net_private_last_error();
            break;

      case DATAGRAM_SENDER:
            /* Nothing further to do */
            break;

      case STREAM_SERVER:
            /* Try to avoid socket reuse timing issues on TCP server sockets */
            vc_container_net_private_set_reusable(sock, true);

            /* Allow any source address */
            socket_clear_address(p->ai_addr);

            if (bind(sock, p->ai_addr, p->ai_addrlen) == SOCKET_ERROR)
               status = vc_container_net_private_last_error();
            break;

      case DATAGRAM_RECEIVER:
            /* Allow any source address */
            socket_clear_address(p->ai_addr);

            if (bind(sock, p->ai_addr, p->ai_addrlen) == SOCKET_ERROR)
               status = vc_container_net_private_last_error();
            break;
      }

      if (status == VC_CONTAINER_NET_SUCCESS)
      {
         /* Save addressing information for later use */
         p_ctx->to_addr_len = p->ai_addrlen;
         memcpy(&p_ctx->to_addr, p->ai_addr, p->ai_addrlen);
      } else {
         vc_container_net_private_close(sock);   /* Try next entry in list */
         sock = INVALID_SOCKET;
      }
   }

   freeaddrinfo(info);

   if (sock == INVALID_SOCKET)
   {
      LOG_ERROR(NULL, "vc_container_net_open: failed to open socket: %d", status);
      goto error;
   }

   p_ctx->socket = sock;
   p_ctx->max_datagram_size = vc_container_net_private_maximum_datagram_size(sock);
   p_ctx->read_timeout_ms = INFINITE_TIMEOUT_MS;

   if (p_status)
      *p_status = VC_CONTAINER_NET_SUCCESS;

   return p_ctx;

error:
   if (p_status)
      *p_status = status;
   (void)vc_container_net_close(p_ctx);
   return NULL;
}