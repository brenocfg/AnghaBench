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
typedef  int /*<<< orphan*/  VC_CONTAINER_NET_T ;

/* Variables and functions */
 int VC_CONTAINER_NET_SUCCESS ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_container_net_close (int /*<<< orphan*/ *) ; 
 size_t vc_container_net_maximum_datagram_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vc_container_net_open (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int*) ; 
 size_t vc_container_net_read (int /*<<< orphan*/ *,char*,size_t) ; 
 int vc_container_net_status (int /*<<< orphan*/ *) ; 

int main(int argc, char **argv)
{
   VC_CONTAINER_NET_T *sock;
   vc_container_net_status_t status;
   char *buffer;
   size_t buffer_size;
   size_t received;

   if (argc < 2)
   {
      printf("Usage:\n%s <port>\n", argv[0]);
      return 1;
   }

   sock = vc_container_net_open(NULL, argv[1], 0, &status);
   if (!sock)
   {
      printf("vc_container_net_open failed: %d\n", status);
      return 2;
   }

   buffer_size = vc_container_net_maximum_datagram_size(sock);
   buffer = (char *)malloc(buffer_size);
   if (!buffer)
   {
      vc_container_net_close(sock);
      printf("Failure allocating buffer\n");
      return 3;
   }

   while ((received = vc_container_net_read(sock, buffer, buffer_size)) != 0)
   {
      char *ptr = buffer;

      while (received--)
         putchar(*ptr++);
   }

   if (vc_container_net_status(sock) != VC_CONTAINER_NET_SUCCESS)
   {
      printf("vc_container_net_read failed: %d\n", vc_container_net_status(sock));
   }

   vc_container_net_close(sock);

   return 0;
}