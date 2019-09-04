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
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_2__ {int length; int /*<<< orphan*/  type; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  TYPE_1__ ASN1_TIME ;

/* Variables and functions */
 int /*<<< orphan*/ * OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int StrLen (char*) ; 
 int SystemToStr (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_ASN1_UTCTIME ; 

bool SystemToAsn1Time(void *asn1_time, SYSTEMTIME *s)
{
	char tmp[20];
	ASN1_TIME *t;
	// Validate arguments
	if (asn1_time == NULL || s == NULL)
	{
		return false;
	}

	if (SystemToStr(tmp, sizeof(tmp), s) == false)
	{
		return false;
	}
	t = (ASN1_TIME *)asn1_time;
	if (t->data == NULL || t->length < sizeof(tmp))
	{
		t->data = OPENSSL_malloc(sizeof(tmp));
	}
	StrCpy((char *)t->data, t->length, tmp);
	t->length = StrLen(tmp);
	t->type = V_ASN1_UTCTIME;

	return true;
}