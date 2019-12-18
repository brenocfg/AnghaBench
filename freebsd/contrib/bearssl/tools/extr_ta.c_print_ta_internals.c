#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  qlen; int /*<<< orphan*/  q; } ;
struct TYPE_9__ {int /*<<< orphan*/  elen; int /*<<< orphan*/  e; int /*<<< orphan*/  nlen; int /*<<< orphan*/  n; } ;
struct TYPE_11__ {TYPE_3__ ec; TYPE_2__ rsa; } ;
struct TYPE_12__ {int key_type; TYPE_4__ key; } ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_13__ {TYPE_5__ pkey; TYPE_1__ dn; } ;
typedef  TYPE_6__ br_x509_trust_anchor ;

/* Variables and functions */
#define  BR_KEYTYPE_EC 129 
#define  BR_KEYTYPE_RSA 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  print_blob (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
print_ta_internals(br_x509_trust_anchor *ta, long ctr)
{
	char tmp[25];

	sprintf(tmp, "TA%ld_DN", ctr);
	print_blob(tmp, ta->dn.data, ta->dn.len);
	switch (ta->pkey.key_type) {
	case BR_KEYTYPE_RSA:
		sprintf(tmp, "TA%ld_RSA_N", ctr);
		print_blob(tmp, ta->pkey.key.rsa.n, ta->pkey.key.rsa.nlen);
		sprintf(tmp, "TA%ld_RSA_E", ctr);
		print_blob(tmp, ta->pkey.key.rsa.e, ta->pkey.key.rsa.elen);
		break;
	case BR_KEYTYPE_EC:
		sprintf(tmp, "TA%ld_EC_Q", ctr);
		print_blob(tmp, ta->pkey.key.ec.q, ta->pkey.key.ec.qlen);
		break;
	default:
		fprintf(stderr, "ERROR: unknown anchor key type '%d'\n",
			ta->pkey.key_type);
		return -1;
	}
	return 0;
}