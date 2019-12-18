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
struct TYPE_10__ {int /*<<< orphan*/  q; } ;
struct TYPE_9__ {int /*<<< orphan*/  e; int /*<<< orphan*/  n; } ;
struct TYPE_11__ {TYPE_3__ ec; TYPE_2__ rsa; } ;
struct TYPE_12__ {int key_type; TYPE_4__ key; } ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct TYPE_13__ {TYPE_5__ pkey; TYPE_1__ dn; } ;
typedef  TYPE_6__ br_x509_trust_anchor ;

/* Variables and functions */
#define  BR_KEYTYPE_EC 129 
#define  BR_KEYTYPE_RSA 128 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ ) ; 

void
free_ta_contents(br_x509_trust_anchor *ta)
{
	xfree(ta->dn.data);
	switch (ta->pkey.key_type) {
	case BR_KEYTYPE_RSA:
		xfree(ta->pkey.key.rsa.n);
		xfree(ta->pkey.key.rsa.e);
		break;
	case BR_KEYTYPE_EC:
		xfree(ta->pkey.key.ec.q);
		break;
	}
}