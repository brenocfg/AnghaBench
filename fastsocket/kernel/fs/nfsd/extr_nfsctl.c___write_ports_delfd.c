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
typedef  int ssize_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SIMPLE_TRANSACTION_LIMIT ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nfsd_serv ; 
 int svc_sock_names (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t __write_ports_delfd(char *buf)
{
	char *toclose;
	int len = 0;

	toclose = kstrdup(buf + 1, GFP_KERNEL);
	if (toclose == NULL)
		return -ENOMEM;

	if (nfsd_serv != NULL)
		len = svc_sock_names(nfsd_serv, buf,
					SIMPLE_TRANSACTION_LIMIT, toclose);
	kfree(toclose);
	return len;
}