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
struct socket {int dummy; } ;
struct kvec {int iov_len; void* iov_base; } ;

/* Variables and functions */
 int do_send (struct socket*,struct kvec*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _send(struct socket *sock, const void *buff, int len)
{
	struct kvec vec;
	vec.iov_base = (void *) buff;
	vec.iov_len = len;
	return do_send(sock, &vec, 1, len, 0);
}