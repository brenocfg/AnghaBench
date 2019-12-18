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
struct TYPE_2__ {int /*<<< orphan*/ * dh; } ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  DH ;

/* Variables and functions */
 TYPE_1__* dh_param ; 

DH *TmpDhCallback(SSL *ssl, int is_export, int keylength)
{
	DH *ret = NULL;

	if (dh_param != NULL)
	{
		ret = dh_param->dh;
	}

	return ret;
}