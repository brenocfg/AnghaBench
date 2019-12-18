#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* data; } ;
struct TYPE_4__ {size_t* x; } ;
struct key {TYPE_1__ payload; TYPE_2__ type_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  is_ip (void const*,size_t) ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,size_t) ; 

__attribute__((used)) static int
dns_resolver_instantiate(struct key *key, const void *data,
		size_t datalen)
{
	int rc = 0;
	char *ip;

	/* make sure this looks like an address */
	if (!is_ip(data, datalen))
		return -EINVAL;

	ip = kmalloc(datalen + 1, GFP_KERNEL);
	if (!ip)
		return -ENOMEM;

	memcpy(ip, data, datalen);
	ip[datalen] = '\0';

	key->type_data.x[0] = datalen;
	key->payload.data = ip;

	return rc;
}