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
typedef  scalar_t__ rpc_authflavor_t ;

/* Variables and functions */
#define  RPC_AUTH_GSS_KRB5 139 
#define  RPC_AUTH_GSS_KRB5I 138 
#define  RPC_AUTH_GSS_KRB5P 137 
#define  RPC_AUTH_GSS_LKEY 136 
#define  RPC_AUTH_GSS_LKEYI 135 
#define  RPC_AUTH_GSS_LKEYP 134 
#define  RPC_AUTH_GSS_SPKM 133 
#define  RPC_AUTH_GSS_SPKMI 132 
#define  RPC_AUTH_GSS_SPKMP 131 
#define  RPC_AUTH_NULL 130 
#define  RPC_AUTH_UNIX 129 
#define  UINT_MAX 128 

__attribute__((used)) static const char *nfs_pseudoflavour_to_name(rpc_authflavor_t flavour)
{
	static const struct {
		rpc_authflavor_t flavour;
		const char *str;
	} sec_flavours[] = {
		{ RPC_AUTH_NULL, "null" },
		{ RPC_AUTH_UNIX, "sys" },
		{ RPC_AUTH_GSS_KRB5, "krb5" },
		{ RPC_AUTH_GSS_KRB5I, "krb5i" },
		{ RPC_AUTH_GSS_KRB5P, "krb5p" },
		{ RPC_AUTH_GSS_LKEY, "lkey" },
		{ RPC_AUTH_GSS_LKEYI, "lkeyi" },
		{ RPC_AUTH_GSS_LKEYP, "lkeyp" },
		{ RPC_AUTH_GSS_SPKM, "spkm" },
		{ RPC_AUTH_GSS_SPKMI, "spkmi" },
		{ RPC_AUTH_GSS_SPKMP, "spkmp" },
		{ UINT_MAX, "unknown" }
	};
	int i;

	for (i = 0; sec_flavours[i].flavour != UINT_MAX; i++) {
		if (sec_flavours[i].flavour == flavour)
			break;
	}
	return sec_flavours[i].str;
}