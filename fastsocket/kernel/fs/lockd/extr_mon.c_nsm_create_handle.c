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
typedef  char sockaddr ;
struct nsm_handle {char* sm_name; size_t sm_addrlen; int /*<<< orphan*/  sm_addrbuf; int /*<<< orphan*/  sm_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct nsm_handle* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t const) ; 
 char* nsm_addr (struct nsm_handle*) ; 
 int /*<<< orphan*/  nsm_init_private (struct nsm_handle*) ; 
 scalar_t__ rpc_ntop (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nsm_handle *nsm_create_handle(const struct sockaddr *sap,
					    const size_t salen,
					    const char *hostname,
					    const size_t hostname_len)
{
	struct nsm_handle *new;

	new = kzalloc(sizeof(*new) + hostname_len + 1, GFP_KERNEL);
	if (unlikely(new == NULL))
		return NULL;

	atomic_set(&new->sm_count, 1);
	new->sm_name = (char *)(new + 1);
	memcpy(nsm_addr(new), sap, salen);
	new->sm_addrlen = salen;
	nsm_init_private(new);

	if (rpc_ntop(nsm_addr(new), new->sm_addrbuf,
					sizeof(new->sm_addrbuf)) == 0)
		(void)snprintf(new->sm_addrbuf, sizeof(new->sm_addrbuf),
				"unsupported address family");
	memcpy(new->sm_name, hostname, hostname_len);
	new->sm_name[hostname_len] = '\0';

	return new;
}