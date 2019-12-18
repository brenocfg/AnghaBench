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
struct net {int dummy; } ;
struct ip_options {int /*<<< orphan*/  __data; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ip_options* ip_options_get_alloc (int) ; 
 int ip_options_get_finish (struct net*,struct ip_options**,struct ip_options*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 

int ip_options_get(struct net *net, struct ip_options **optp,
		   unsigned char *data, int optlen)
{
	struct ip_options *opt = ip_options_get_alloc(optlen);

	if (!opt)
		return -ENOMEM;
	if (optlen)
		memcpy(opt->__data, data, optlen);
	return ip_options_get_finish(net, optp, opt, optlen);
}