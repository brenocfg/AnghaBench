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
struct socket_buffer {size_t bufsz; } ;

/* Variables and functions */
 size_t buf_used (struct socket_buffer*) ; 

__attribute__((used)) static size_t buf_remaining(struct socket_buffer *sbuf)
{
   return sbuf->bufsz - buf_used(sbuf) - 1;
}