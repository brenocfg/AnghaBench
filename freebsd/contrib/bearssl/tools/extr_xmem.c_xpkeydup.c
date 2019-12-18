#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  qlen; void* q; int /*<<< orphan*/  curve; } ;
struct TYPE_8__ {int /*<<< orphan*/  elen; void* e; int /*<<< orphan*/  nlen; void* n; } ;
struct TYPE_10__ {TYPE_2__ ec; TYPE_1__ rsa; } ;
struct TYPE_11__ {int key_type; TYPE_3__ key; } ;
typedef  TYPE_4__ br_x509_pkey ;

/* Variables and functions */
#define  BR_KEYTYPE_EC 129 
#define  BR_KEYTYPE_RSA 128 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  stderr ; 
 void* xblobdup (void*,int /*<<< orphan*/ ) ; 
 TYPE_4__* xmalloc (int) ; 

br_x509_pkey *
xpkeydup(const br_x509_pkey *pk)
{
	br_x509_pkey *pk2;

	pk2 = xmalloc(sizeof *pk2);
	pk2->key_type = pk->key_type;
	switch (pk->key_type) {
	case BR_KEYTYPE_RSA:
		pk2->key.rsa.n = xblobdup(pk->key.rsa.n, pk->key.rsa.nlen);
		pk2->key.rsa.nlen = pk->key.rsa.nlen;
		pk2->key.rsa.e = xblobdup(pk->key.rsa.e, pk->key.rsa.elen);
		pk2->key.rsa.elen = pk->key.rsa.elen;
		break;
	case BR_KEYTYPE_EC:
		pk2->key.ec.curve = pk->key.ec.curve;
		pk2->key.ec.q = xblobdup(pk->key.ec.q, pk->key.ec.qlen);
		pk2->key.ec.qlen = pk->key.ec.qlen;
		break;
	default:
#ifndef _STANDALONE
		fprintf(stderr, "Unknown public key type: %u\n",
			(unsigned)pk->key_type);
		exit(EXIT_FAILURE);
#else 
; 
#endif
	}
	return pk2;
}