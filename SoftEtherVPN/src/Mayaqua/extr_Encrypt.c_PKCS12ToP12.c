#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * pkcs12; } ;
typedef  int /*<<< orphan*/  PKCS12 ;
typedef  TYPE_1__ P12 ;

/* Variables and functions */
 TYPE_1__* ZeroMalloc (int) ; 

P12 *PKCS12ToP12(PKCS12 *pkcs12)
{
	P12 *p12;
	// Validate arguments
	if (pkcs12 == NULL)
	{
		return NULL;
	}

	p12 = ZeroMalloc(sizeof(P12));
	p12->pkcs12 = pkcs12;

	return p12;
}