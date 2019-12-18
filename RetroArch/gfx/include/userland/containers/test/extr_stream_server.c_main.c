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
typedef  int vc_container_net_status_t ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  VC_CONTAINER_NET_T ;

/* Variables and functions */
 int MAX_BUFFER_LEN ; 
 int MAX_NAME_LEN ; 
 int VC_CONTAINER_NET_ERROR_CONNECTION_LOST ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_OPEN_FLAG_STREAM ; 
 int VC_CONTAINER_NET_SUCCESS ; 
 scalar_t__ isalpha (unsigned char) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int vc_container_net_accept (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  vc_container_net_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_container_net_get_client_name (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  vc_container_net_get_client_port (int /*<<< orphan*/ *,unsigned short*) ; 
 int vc_container_net_listen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * vc_container_net_open (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int*) ; 
 size_t vc_container_net_read (int /*<<< orphan*/ *,char*,int) ; 
 int vc_container_net_status (int /*<<< orphan*/ *) ; 
 size_t vc_container_net_write (int /*<<< orphan*/ *,char*,size_t) ; 

int main(int argc, char **argv)
{
   VC_CONTAINER_NET_T *server_sock, *sock;
   vc_container_net_status_t status;
   char buffer[MAX_BUFFER_LEN];
   char name[MAX_NAME_LEN];
   unsigned short port;
   int ii, connections = 1;
   size_t received;

   if (argc < 2)
   {
      printf("Usage:\n%s <port> [<connections>]\n", argv[0]);
      return 1;
   }

   server_sock = vc_container_net_open(NULL, argv[1], VC_CONTAINER_NET_OPEN_FLAG_STREAM, &status);
   if (!server_sock)
   {
      printf("vc_container_net_open failed: %d\n", status);
      return 2;
   }

   if (argc > 2)
   {
      sscanf(argv[2], "%d", &connections);
   }

   status = vc_container_net_listen(server_sock, connections);
   if (status != VC_CONTAINER_NET_SUCCESS)
   {
      printf("vc_container_net_listen failed: %d\n", status);
      vc_container_net_close(server_sock);
      return 3;
   }

   for (ii = 0; ii < connections; ii++)
   {
      status = vc_container_net_accept(server_sock, &sock);
      if (status != VC_CONTAINER_NET_SUCCESS)
      {
         printf("vc_container_net_accept failed: %d\n", status);
         vc_container_net_close(server_sock);
         return 3;
      }

      strcpy(name, "<unknown>");
      vc_container_net_get_client_name(sock, name, sizeof(name));
      vc_container_net_get_client_port(sock, &port);
      printf("Connection from %s:%hu\n", name, port);

      while ((received = vc_container_net_read(sock, buffer, sizeof(buffer) - 1)) != 0)
      {
         char *ptr = buffer;
         size_t jj;

         printf("Rx:");

         /* Flip case and echo data back to client */
         for (jj = 0; jj < received; jj++, ptr++)
         {
            char c = *ptr;

            putchar(c);
            if (isalpha((unsigned char)c))
               *ptr ^= 0x20;  /* Swaps case of ASCII alphabetic characters */
         }

         ptr = buffer;

         printf("Tx:");
         while (received)
         {
            size_t sent;

            sent = vc_container_net_write(sock, ptr, received);
            if (!sent)
            {
               status = vc_container_net_status(sock);
               printf("vc_container_net_write failed: %d\n", status);
               break;
            }

            /* Print out bytes actually sent */
            while (sent--)
            {
               received--;
               putchar(*ptr++);
            }
         }
      }

      status = vc_container_net_status(sock);

      if (status != VC_CONTAINER_NET_SUCCESS && status != VC_CONTAINER_NET_ERROR_CONNECTION_LOST)
         break;

      vc_container_net_close(sock);
   }

   if (status != VC_CONTAINER_NET_SUCCESS)
   {
      printf("vc_container_net_read failed: %d\n", status);
   }

   vc_container_net_close(server_sock);

   return 0;
}