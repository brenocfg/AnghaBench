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
struct asn1_oid {int len; int* oid; } ;

/* Variables and functions */

__attribute__((used)) static int x509_id_ce_oid(struct asn1_oid *oid)
{
	/* id-ce arc from X.509 for standard X.509v3 extensions */
	return oid->len >= 4 &&
		oid->oid[0] == 2 /* joint-iso-ccitt */ &&
		oid->oid[1] == 5 /* ds */ &&
		oid->oid[2] == 29 /* id-ce */;
}