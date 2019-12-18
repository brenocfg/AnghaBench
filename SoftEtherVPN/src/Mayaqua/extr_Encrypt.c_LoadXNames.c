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
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_3__ {void* subject_name; void* issuer_name; int /*<<< orphan*/ * x509; } ;
typedef  TYPE_1__ X ;

/* Variables and functions */
 void* X509NameToName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_get_issuer_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_get_subject_name (int /*<<< orphan*/ *) ; 

void LoadXNames(X *x)
{
	X509 *x509;
	// Validate arguments
	if (x == NULL)
	{
		return;
	}

	x509 = x->x509;
	x->issuer_name = X509NameToName(X509_get_issuer_name(x509));
	x->subject_name = X509NameToName(X509_get_subject_name(x509));
}