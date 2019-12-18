#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  qlen; int /*<<< orphan*/  q; int /*<<< orphan*/  curve; } ;
struct TYPE_7__ {int /*<<< orphan*/  elen; int /*<<< orphan*/  e; int /*<<< orphan*/  nlen; int /*<<< orphan*/  n; } ;
struct TYPE_9__ {TYPE_2__ ec; TYPE_1__ rsa; } ;
struct TYPE_10__ {int key_type; TYPE_3__ key; } ;
typedef  TYPE_4__ br_x509_pkey ;

/* Variables and functions */
#define  BR_KEYTYPE_EC 129 
#define  BR_KEYTYPE_RSA 128 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  eqbigint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
eqpkey(const br_x509_pkey *pk1, const br_x509_pkey *pk2)
{
	if (pk1 == pk2) {
		return 1;
	}
	if (pk1 == NULL || pk2 == NULL) {
		return 0;
	}
	if (pk1->key_type != pk2->key_type) {
		return 0;
	}
	switch (pk1->key_type) {
	case BR_KEYTYPE_RSA:
		return eqbigint(pk1->key.rsa.n, pk1->key.rsa.nlen,
			pk2->key.rsa.n, pk2->key.rsa.nlen)
			&& eqbigint(pk1->key.rsa.e, pk1->key.rsa.elen,
			pk2->key.rsa.e, pk2->key.rsa.elen);
	case BR_KEYTYPE_EC:
		return pk1->key.ec.curve == pk2->key.ec.curve
			&& pk1->key.ec.qlen == pk2->key.ec.qlen
			&& memcmp(pk1->key.ec.q,
				pk2->key.ec.q, pk1->key.ec.qlen) == 0;
	default:
		fprintf(stderr, "unknown key type: %d\n", pk1->key_type);
		exit(EXIT_FAILURE);
		break;
	}
	return 0;
}