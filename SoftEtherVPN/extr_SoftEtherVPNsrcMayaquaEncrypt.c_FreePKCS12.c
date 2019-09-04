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
typedef  int /*<<< orphan*/  PKCS12 ;

/* Variables and functions */
 int /*<<< orphan*/  PKCS12_free (int /*<<< orphan*/ *) ; 

void FreePKCS12(PKCS12 *pkcs12)
{
	// Validate arguments
	if (pkcs12 == NULL)
	{
		return;
	}

	PKCS12_free(pkcs12);
}