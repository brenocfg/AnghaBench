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
struct TYPE_4__ {int /*<<< orphan*/  pkcs12; } ;
typedef  TYPE_1__ P12 ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreePKCS12 (int /*<<< orphan*/ ) ; 

void FreeP12(P12 *p12)
{
	// Validate arguments
	if (p12 == NULL)
	{
		return;
	}

	FreePKCS12(p12->pkcs12);
	Free(p12);
}