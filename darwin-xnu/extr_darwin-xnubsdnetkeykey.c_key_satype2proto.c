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
typedef  int u_int8_t ;
typedef  int /*<<< orphan*/  u_int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_AH ; 
 int /*<<< orphan*/  IPPROTO_ESP ; 
 int /*<<< orphan*/  IPPROTO_IPCOMP ; 
 int /*<<< orphan*/  IPSEC_PROTO_ANY ; 
#define  SADB_SATYPE_AH 131 
#define  SADB_SATYPE_ESP 130 
#define  SADB_SATYPE_UNSPEC 129 
#define  SADB_X_SATYPE_IPCOMP 128 

__attribute__((used)) static u_int16_t
key_satype2proto(
				 u_int8_t satype)
{
	switch (satype) {
		case SADB_SATYPE_UNSPEC:
			return IPSEC_PROTO_ANY;
		case SADB_SATYPE_AH:
			return IPPROTO_AH;
		case SADB_SATYPE_ESP:
			return IPPROTO_ESP;
		case SADB_X_SATYPE_IPCOMP:
			return IPPROTO_IPCOMP;
		default:
			return 0;
	}
	/* NOTREACHED */
}