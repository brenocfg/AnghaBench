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
typedef  int /*<<< orphan*/  send_buffer ;
typedef  int /*<<< orphan*/  recv_buffer ;
typedef  int /*<<< orphan*/  VC_CONTAINER_NET_T ;

/* Variables and functions */
 int MAX_BUFFER_LEN ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_CONTROL_SET_READ_TIMEOUT_MS ; 
 int VC_CONTAINER_NET_ERROR_TIMED_OUT ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_OPEN_FLAG_STREAM ; 
 int VC_CONTAINER_NET_SUCCESS ; 
 int /*<<< orphan*/  YIELD_PERIOD_MS ; 
 int /*<<< orphan*/  local_net_control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nb_char_available () ; 
 char nb_get_char () ; 
 int /*<<< orphan*/  nb_put_char (char) ; 
 int /*<<< orphan*/  nb_set_nonblocking_input (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  vc_container_net_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vc_container_net_open (char*,char*,int /*<<< orphan*/ ,int*) ; 
 size_t vc_container_net_read (int /*<<< orphan*/ *,char*,int) ; 
 int vc_container_net_status (int /*<<< orphan*/ *) ; 
 int vc_container_net_write (int /*<<< orphan*/ *,char*,int) ; 

int main(int argc, char **argv)
{
   VC_CONTAINER_NET_T *sock;
   vc_container_net_status_t status;
   char send_buffer[MAX_BUFFER_LEN];
   char recv_buffer[MAX_BUFFER_LEN];
   int ready = 1;
   int to_send = 0;
   size_t received;

   if (argc < 3)
   {
      printf("Usage:\n%s <address> <port>\n", argv[0]);
      return 1;
   }

   sock = vc_container_net_open(argv[1], argv[2], VC_CONTAINER_NET_OPEN_FLAG_STREAM, &status);
   if (!sock)
   {
      printf("vc_container_net_open failed: %d\n", status);
      return 2;
   }

   /* Use non-blocking I/O for both network and console */
   local_net_control(sock, VC_CONTAINER_NET_CONTROL_SET_READ_TIMEOUT_MS, YIELD_PERIOD_MS);
   nb_set_nonblocking_input(1);

   while (ready)
   {
      if (nb_char_available())
      {
         char c = nb_get_char();

         if (c == 26)   /* CTRL+Z */
            break;

         send_buffer[to_send++] = c;

         if (c == '\r') /* Translate CR into CRLF */
         {
            c = '\n';
            nb_put_char(c);
            send_buffer[to_send++] = c;
         }

         if (c == '\n' || to_send == sizeof(send_buffer) - 1)  /* Allow for next character needing translation */
         {
            int already_sent = 0, sent;

            /* Send a line at a time */
            while (to_send)
            {
               sent = vc_container_net_write(sock, send_buffer + already_sent, to_send);
               if (!sent)
               {
                  printf("vc_container_net_write failed: %d\n", vc_container_net_status(sock));
                  to_send = 0;
                  ready = 0;
                  break;
               }
               to_send -= sent;
               already_sent += sent;
            }
         }
      }

      /* Read back and print any data from the server */
      received = vc_container_net_read(sock, recv_buffer, sizeof(recv_buffer) - 1);
      if (received)
      {
         char *ptr = recv_buffer;

         while (received--)
            nb_put_char(*ptr++);
      } else {
         vc_container_net_status_t net_status = vc_container_net_status(sock);

         if (net_status != VC_CONTAINER_NET_ERROR_TIMED_OUT && net_status != VC_CONTAINER_NET_SUCCESS)
         {
            printf("vc_container_net_read failed: %d\n", net_status);
            ready = 0;
         }
      }
   }

   nb_set_nonblocking_input(0);

   vc_container_net_close(sock);

   return 0;
}