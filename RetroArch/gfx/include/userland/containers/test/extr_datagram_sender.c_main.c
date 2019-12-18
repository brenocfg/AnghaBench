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
 scalar_t__ fgets (char*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  vc_container_net_close (int /*<<< orphan*/ *) ; 
 size_t vc_container_net_maximum_datagram_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vc_container_net_open (char*,char*,int /*<<< orphan*/ ,int*) ; 
 int vc_container_net_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_container_net_write (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

int main(int argc, char **argv)
{
   VC_CONTAINER_NET_T *sock;
   vc_container_net_status_t status;
   char *buffer;
   size_t buffer_size;

   if (argc < 3)
   {
      printf("Usage:\n%s <address> <port>\n", argv[0]);
      return 1;
   }

   sock = vc_container_net_open(argv[1], argv[2], 0, &status);
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

   printf("Don't enter more than %d characters in one line!\n", (int)buffer_size);

   while (fgets(buffer, buffer_size, stdin))
   {
      if (!vc_container_net_write(sock, buffer, strlen(buffer)))
      {
         printf("vc_container_net_write failed: %d\n", vc_container_net_status(sock));
         break;
      }
   }

   vc_container_net_close(sock);

   return 0;
}