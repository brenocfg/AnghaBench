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
typedef  int /*<<< orphan*/  substring_t ;
struct nfs_parsed_mount_data {int auth_flavor_len; int /*<<< orphan*/  flags; int /*<<< orphan*/ * auth_flavors; } ;

/* Variables and functions */
 int MAX_OPT_ARGS ; 
 int /*<<< orphan*/  MOUNT ; 
 int /*<<< orphan*/  NFS_MOUNT_SECFLAVOUR ; 
#define  Opt_sec_krb5 138 
#define  Opt_sec_krb5i 137 
#define  Opt_sec_krb5p 136 
#define  Opt_sec_lkey 135 
#define  Opt_sec_lkeyi 134 
#define  Opt_sec_lkeyp 133 
#define  Opt_sec_none 132 
#define  Opt_sec_spkm 131 
#define  Opt_sec_spkmi 130 
#define  Opt_sec_spkmp 129 
#define  Opt_sec_sys 128 
 int /*<<< orphan*/  RPC_AUTH_GSS_KRB5 ; 
 int /*<<< orphan*/  RPC_AUTH_GSS_KRB5I ; 
 int /*<<< orphan*/  RPC_AUTH_GSS_KRB5P ; 
 int /*<<< orphan*/  RPC_AUTH_GSS_LKEY ; 
 int /*<<< orphan*/  RPC_AUTH_GSS_LKEYI ; 
 int /*<<< orphan*/  RPC_AUTH_GSS_LKEYP ; 
 int /*<<< orphan*/  RPC_AUTH_GSS_SPKM ; 
 int /*<<< orphan*/  RPC_AUTH_GSS_SPKMI ; 
 int /*<<< orphan*/  RPC_AUTH_GSS_SPKMP ; 
 int /*<<< orphan*/  RPC_AUTH_NULL ; 
 int /*<<< orphan*/  RPC_AUTH_UNIX ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,char*) ; 
 int match_token (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_secflavor_tokens ; 

__attribute__((used)) static int nfs_parse_security_flavors(char *value,
				      struct nfs_parsed_mount_data *mnt)
{
	substring_t args[MAX_OPT_ARGS];

	dfprintk(MOUNT, "NFS: parsing sec=%s option\n", value);

	switch (match_token(value, nfs_secflavor_tokens, args)) {
	case Opt_sec_none:
		mnt->auth_flavors[0] = RPC_AUTH_NULL;
		break;
	case Opt_sec_sys:
		mnt->auth_flavors[0] = RPC_AUTH_UNIX;
		break;
	case Opt_sec_krb5:
		mnt->auth_flavors[0] = RPC_AUTH_GSS_KRB5;
		break;
	case Opt_sec_krb5i:
		mnt->auth_flavors[0] = RPC_AUTH_GSS_KRB5I;
		break;
	case Opt_sec_krb5p:
		mnt->auth_flavors[0] = RPC_AUTH_GSS_KRB5P;
		break;
	case Opt_sec_lkey:
		mnt->auth_flavors[0] = RPC_AUTH_GSS_LKEY;
		break;
	case Opt_sec_lkeyi:
		mnt->auth_flavors[0] = RPC_AUTH_GSS_LKEYI;
		break;
	case Opt_sec_lkeyp:
		mnt->auth_flavors[0] = RPC_AUTH_GSS_LKEYP;
		break;
	case Opt_sec_spkm:
		mnt->auth_flavors[0] = RPC_AUTH_GSS_SPKM;
		break;
	case Opt_sec_spkmi:
		mnt->auth_flavors[0] = RPC_AUTH_GSS_SPKMI;
		break;
	case Opt_sec_spkmp:
		mnt->auth_flavors[0] = RPC_AUTH_GSS_SPKMP;
		break;
	default:
		return 0;
	}

	mnt->flags |= NFS_MOUNT_SECFLAVOUR;
	mnt->auth_flavor_len = 1;
	return 1;
}