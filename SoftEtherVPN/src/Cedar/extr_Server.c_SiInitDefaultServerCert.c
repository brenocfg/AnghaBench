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
typedef  int /*<<< orphan*/  X ;
struct TYPE_3__ {int /*<<< orphan*/  Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  int /*<<< orphan*/  K ;

/* Variables and functions */
 int /*<<< orphan*/  FreeK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetCedarCert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiGenerateDefaultCert (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

void SiInitDefaultServerCert(SERVER *s)
{
	X *x = NULL;
	K *k = NULL;
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	// Generate a server certificate and private key
	SiGenerateDefaultCert(&x, &k);

	// Configure
	SetCedarCert(s->Cedar, x, k);

	FreeX(x);
	FreeK(k);
}