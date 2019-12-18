#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  x509; void* notAfter; void* notBefore; } ;
typedef  TYPE_1__ X ;
typedef  int /*<<< orphan*/  ASN1_TIME ;

/* Variables and functions */
 void* Asn1TimeToUINT64 (int /*<<< orphan*/ *) ; 
 scalar_t__ X509_get0_notAfter (int /*<<< orphan*/ ) ; 
 scalar_t__ X509_get0_notBefore (int /*<<< orphan*/ ) ; 

void LoadXDates(X *x)
{
	// Validate arguments
	if (x == NULL)
	{
		return;
	}

	x->notBefore = Asn1TimeToUINT64((ASN1_TIME *)X509_get0_notBefore(x->x509));
	x->notAfter = Asn1TimeToUINT64((ASN1_TIME *)X509_get0_notAfter(x->x509));
}