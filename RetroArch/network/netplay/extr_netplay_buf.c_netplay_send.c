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
struct socket_buffer {size_t bufsz; size_t end; size_t data; } ;

/* Variables and functions */
 size_t buf_remaining (struct socket_buffer*) ; 
 int /*<<< orphan*/  memcpy (size_t,void const*,size_t) ; 
 int /*<<< orphan*/  netplay_send_flush (struct socket_buffer*,int,int) ; 
 int /*<<< orphan*/  socket_send_all_blocking (int,void const*,size_t,int) ; 

bool netplay_send(struct socket_buffer *sbuf, int sockfd, const void *buf,
   size_t len)
{
   if (buf_remaining(sbuf) < len)
   {
      /* Need to force a blocking send */
      if (!netplay_send_flush(sbuf, sockfd, true))
         return false;
   }

   if (buf_remaining(sbuf) < len)
   {
      /* Can only be that this is simply too big for our buffer, in which case
       * we just need to do a blocking send */
      if (!socket_send_all_blocking(sockfd, buf, len, false))
         return false;
      return true;
   }

   /* Copy it into our buffer */
   if (sbuf->bufsz - sbuf->end < len)
   {
      /* Half at a time */
      size_t chunka = sbuf->bufsz - sbuf->end,
             chunkb = len - chunka;
      memcpy(sbuf->data + sbuf->end, buf, chunka);
      memcpy(sbuf->data, (const unsigned char *) buf + chunka, chunkb);
      sbuf->end = chunkb;

   }
   else
   {
      /* Straight in */
      memcpy(sbuf->data + sbuf->end, buf, len);
      sbuf->end += len;

   }

   return true;
}