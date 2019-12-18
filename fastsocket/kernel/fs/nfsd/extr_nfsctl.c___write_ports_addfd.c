#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  sv_nrthreads; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SIMPLE_TRANSACTION_LIMIT ; 
 int get_int (char**,int*) ; 
 int nfsd_create_serv () ; 
 TYPE_1__* nfsd_serv ; 
 int svc_addsock (TYPE_1__*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_destroy (TYPE_1__*) ; 

__attribute__((used)) static ssize_t __write_ports_addfd(char *buf)
{
	char *mesg = buf;
	int fd, err;

	err = get_int(&mesg, &fd);
	if (err != 0 || fd < 0)
		return -EINVAL;

	err = nfsd_create_serv();
	if (err != 0)
		return err;

	err = svc_addsock(nfsd_serv, fd, buf, SIMPLE_TRANSACTION_LIMIT);
	if (err < 0) {
		svc_destroy(nfsd_serv);
		return err;
	}

	/* Decrease the count, but don't shut down the service */
	nfsd_serv->sv_nrthreads--;
	return err;
}