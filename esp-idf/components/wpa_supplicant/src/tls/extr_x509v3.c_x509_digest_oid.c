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
 scalar_t__ x509_rsadsi_oid (struct asn1_oid*) ; 

__attribute__((used)) static int x509_digest_oid(struct asn1_oid *oid)
{
	return oid->len >= 5 &&
		x509_rsadsi_oid(oid) &&
		oid->oid[4] == 2 /* digestAlgorithm */;
}