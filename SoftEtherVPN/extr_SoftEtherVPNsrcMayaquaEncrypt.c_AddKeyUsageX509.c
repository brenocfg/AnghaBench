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
typedef  int /*<<< orphan*/  EXTENDED_KEY_USAGE ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/ * OBJ_nid2obj (int) ; 
 int /*<<< orphan*/  sk_ASN1_OBJECT_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void AddKeyUsageX509(EXTENDED_KEY_USAGE *ex, int nid)
{
	ASN1_OBJECT *obj;
	// Validate arguments
	if (ex == NULL)
	{
		return;
	}

	obj = OBJ_nid2obj(nid);
	if (obj != NULL)
	{
		sk_ASN1_OBJECT_push(ex, obj);
	}
}