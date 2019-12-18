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
struct socket_buffer {unsigned char* data; size_t bufsz; scalar_t__ end; scalar_t__ read; scalar_t__ start; } ;

/* Variables and functions */
 scalar_t__ malloc (size_t) ; 

bool netplay_init_socket_buffer(struct socket_buffer *sbuf, size_t size)
{
   sbuf->data = (unsigned char*)malloc(size);
   if (!sbuf->data)
      return false;
   sbuf->bufsz = size;
   sbuf->start = sbuf->read = sbuf->end = 0;
   return true;
}