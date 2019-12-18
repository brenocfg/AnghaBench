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
struct ccdigest_info {int dummy; } ;
struct TYPE_2__ {struct ccdigest_info const* ccsha1_di; } ;

/* Variables and functions */
 TYPE_1__* g_crypto_funcs ; 

const struct ccdigest_info *
ccsha1_di(void)
{
	if (g_crypto_funcs)
		return (g_crypto_funcs->ccsha1_di);
	return (NULL);
}