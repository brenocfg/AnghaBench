#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
typedef  int /*<<< orphan*/  res ;
struct TYPE_11__ {int /*<<< orphan*/  argop; } ;
typedef  TYPE_3__ nfs_argop4 ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  arg ;
struct TYPE_13__ {int /*<<< orphan*/ * cl_auth; } ;
struct TYPE_10__ {int argarray_len; TYPE_3__* argarray_val; } ;
struct TYPE_9__ {char* utf8string_val; int /*<<< orphan*/  utf8string_len; } ;
struct TYPE_12__ {TYPE_2__ argarray; TYPE_1__ tag; scalar_t__ minorversion; } ;
typedef  int /*<<< orphan*/  COMPOUND4res ;
typedef  TYPE_4__ COMPOUND4args ;
typedef  TYPE_5__ CLIENT ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_PROGRAM ; 
 int /*<<< orphan*/  NFSPROC4_COMPOUND ; 
 int /*<<< orphan*/  NFS_V4 ; 
 int /*<<< orphan*/  OP_PUTROOTFH ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/ * authsys_create_default () ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int clnt_call (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval) ; 
 TYPE_5__* clnt_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clnt_pcreateerror (char*) ; 
 int /*<<< orphan*/  clnt_perror (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ waiting (int volatile*) ; 
 int /*<<< orphan*/  xdr_COMPOUND4args ; 
 int /*<<< orphan*/  xdr_COMPOUND4res ; 

int
dotest(void)
{
	CLIENT *client;
	AUTH *auth;
	COMPOUND4args args;
	COMPOUND4res res;
	enum clnt_stat status;
	struct timeval timeout;
	nfs_argop4 arg[1];
	char *tag = "dtrace test";
	volatile int a = 0;

	while (waiting(&a) == 0)
		continue;

	timeout.tv_sec = 30;
	timeout.tv_usec = 0;

	client = clnt_create("localhost", NFS4_PROGRAM, NFS_V4, "tcp");
	if (client == NULL) {
		clnt_pcreateerror("test");
		return (1);
	}
	auth = authsys_create_default();
	client->cl_auth = auth;
	args.minorversion = 0;
	args.tag.utf8string_len = strlen(tag);
	args.tag.utf8string_val = tag;
	args.argarray.argarray_len = sizeof (arg) / sizeof (nfs_argop4);
	args.argarray.argarray_val = arg;

	arg[0].argop = OP_PUTROOTFH;
	/* no need to manipulate nfs_argop4_u */

	bzero(&res, sizeof (res));

	status = clnt_call(client, NFSPROC4_COMPOUND,
	    xdr_COMPOUND4args, (caddr_t)&args,
	    xdr_COMPOUND4res, (caddr_t)&res,
	    timeout);
	if (status != RPC_SUCCESS) {
		clnt_perror(client, "test");
		return (2);
	}

	return (0);
}