#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct nfsd4_exchange_id {char clientid; int seqid; int flags; scalar_t__ spa_how; } ;
struct nfsd4_compoundres {int dummy; } ;
typedef  int __be32 ;
struct TYPE_2__ {char* nodename; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADJUST_ARGS () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RESERVE_SPACE (int) ; 
 scalar_t__ SP4_NONE ; 
 int /*<<< orphan*/  WRITE32 (int) ; 
 int /*<<< orphan*/  WRITE64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITEMEM (char*,int) ; 
 int XDR_QUADLEN (int) ; 
 int strlen (char*) ; 
 TYPE_1__* utsname () ; 

__attribute__((used)) static __be32
nfsd4_encode_exchange_id(struct nfsd4_compoundres *resp, int nfserr,
			 struct nfsd4_exchange_id *exid)
{
	__be32 *p;
	char *major_id;
	char *server_scope;
	int major_id_sz;
	int server_scope_sz;
	uint64_t minor_id = 0;

	if (nfserr)
		return nfserr;

	major_id = utsname()->nodename;
	major_id_sz = strlen(major_id);
	server_scope = utsname()->nodename;
	server_scope_sz = strlen(server_scope);

	RESERVE_SPACE(
		8 /* eir_clientid */ +
		4 /* eir_sequenceid */ +
		4 /* eir_flags */ +
		4 /* spr_how (SP4_NONE) */ +
		8 /* so_minor_id */ +
		4 /* so_major_id.len */ +
		(XDR_QUADLEN(major_id_sz) * 4) +
		4 /* eir_server_scope.len */ +
		(XDR_QUADLEN(server_scope_sz) * 4) +
		4 /* eir_server_impl_id.count (0) */);

	WRITEMEM(&exid->clientid, 8);
	WRITE32(exid->seqid);
	WRITE32(exid->flags);

	/* state_protect4_r. Currently only support SP4_NONE */
	BUG_ON(exid->spa_how != SP4_NONE);
	WRITE32(exid->spa_how);

	/* The server_owner struct */
	WRITE64(minor_id);      /* Minor id */
	/* major id */
	WRITE32(major_id_sz);
	WRITEMEM(major_id, major_id_sz);

	/* Server scope */
	WRITE32(server_scope_sz);
	WRITEMEM(server_scope, server_scope_sz);

	/* Implementation id */
	WRITE32(0);	/* zero length nfs_impl_id4 array */
	ADJUST_ARGS();
	return 0;
}