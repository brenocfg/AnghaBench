#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ type; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  TYPE_1__ ASN1_TIME ;

/* Variables and functions */
 int /*<<< orphan*/  LocalToSystem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int StrToSystem (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ V_ASN1_GENERALIZEDTIME ; 

bool Asn1TimeToSystem(SYSTEMTIME *s, void *asn1_time)
{
	ASN1_TIME *t;
	// Validate arguments
	if (s == NULL || asn1_time == NULL)
	{
		return false;
	}

	t = (ASN1_TIME *)asn1_time;
	if (StrToSystem(s, (char *)t->data) == false)
	{
		return false;
	}

	if (t->type == V_ASN1_GENERALIZEDTIME)
	{
		LocalToSystem(s, s);
	}

	return true;
}