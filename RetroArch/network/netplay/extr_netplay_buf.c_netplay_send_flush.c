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
struct socket_buffer {scalar_t__ end; scalar_t__ start; scalar_t__ data; scalar_t__ bufsz; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ buf_used (struct socket_buffer*) ; 
 int /*<<< orphan*/  socket_send_all_blocking (int,scalar_t__,scalar_t__,int) ; 
 scalar_t__ socket_send_all_nonblocking (int,scalar_t__,scalar_t__,int) ; 

bool netplay_send_flush(struct socket_buffer *sbuf, int sockfd, bool block)
{
   ssize_t sent;

   if (buf_used(sbuf) == 0)
      return true;

   if (sbuf->end > sbuf->start)
   {
      /* Usual case: Everything's in order */
      if (block)
      {
         if (!socket_send_all_blocking(
                  sockfd, sbuf->data + sbuf->start, buf_used(sbuf), true))
            return false;
         sbuf->start = sbuf->end = 0;

      }
      else
      {
         sent = socket_send_all_nonblocking(sockfd, sbuf->data + sbuf->start, buf_used(sbuf), true);
         if (sent < 0)
            return false;
         sbuf->start += sent;

         if (sbuf->start == sbuf->end)
            sbuf->start = sbuf->end = 0;

      }

   }
   else
   {
      /* Unusual case: Buffer overlaps break */
      if (block)
      {
         if (!socket_send_all_blocking(sockfd, sbuf->data + sbuf->start, sbuf->bufsz - sbuf->start, true))
            return false;
         sbuf->start = 0;
         return netplay_send_flush(sbuf, sockfd, true);

      }
      else
      {
         sent = socket_send_all_nonblocking(sockfd, sbuf->data + sbuf->start, sbuf->bufsz - sbuf->start, true);
         if (sent < 0)
            return false;
         sbuf->start += sent;

         if (sbuf->start >= sbuf->bufsz)
         {
            sbuf->start = 0;
            return netplay_send_flush(sbuf, sockfd, false);

         }

      }

   }

   return true;
}