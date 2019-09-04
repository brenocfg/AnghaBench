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
typedef  int /*<<< orphan*/  X ;
typedef  int /*<<< orphan*/  P12 ;
typedef  int /*<<< orphan*/  K ;

/* Variables and functions */
 int /*<<< orphan*/  FreeK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 int ParseP12 (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

bool IsEncryptedP12(P12 *p12)
{
	X *x;
	K *k;
	// Validate arguments
	if (p12 == NULL)
	{
		return false;
	}

	if (ParseP12(p12, &x, &k, NULL) == true)
	{
		FreeX(x);
		FreeK(k);
		return false;
	}

	return true;
}