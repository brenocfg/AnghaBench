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
typedef  int /*<<< orphan*/  DH_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  DhFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dh_param ; 

void SetDhParam(DH_CTX *dh)
 {
	if (dh_param)
	{
 		DhFree(dh_param);
 	}

 	dh_param = dh;
 }