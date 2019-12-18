#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ftp_provid; } ;
typedef  TYPE_1__ fasttrap_provider_t ;
struct TYPE_4__ {char* dtpv_name; } ;
typedef  TYPE_2__ dtrace_provider_t ;

/* Variables and functions */

__attribute__((used)) static char*
fasttrap_meta_provider_name(void *arg)
{
	fasttrap_provider_t *fprovider = arg;
	dtrace_provider_t *provider = (dtrace_provider_t*)(fprovider->ftp_provid);
	return provider->dtpv_name;
}