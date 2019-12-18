#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int off_t ;
struct TYPE_6__ {int controller; } ;
typedef  TYPE_2__ diva_os_xdi_adapter_t ;
struct TYPE_5__ {int cfg_1; } ;
struct TYPE_7__ {TYPE_1__ capi_cfg; } ;
typedef  TYPE_3__* PISDN_ADAPTER ;

/* Variables and functions */
 int DIVA_XDI_CAPI_CFG_1_GROUP_POPTIMIZATION_ON ; 
 TYPE_3__** IoAdapters ; 
 scalar_t__ sprintf (char*,char*,char*) ; 

__attribute__((used)) static int
read_grp_opt(char *page, char **start, off_t off, int count, int *eof,
	     void *data)
{
	int len = 0;
	diva_os_xdi_adapter_t *a = (diva_os_xdi_adapter_t *) data;
	PISDN_ADAPTER IoAdapter = IoAdapters[a->controller - 1];

	len += sprintf(page + len, "%s\n",
		       (IoAdapter->capi_cfg.
			cfg_1 & DIVA_XDI_CAPI_CFG_1_GROUP_POPTIMIZATION_ON)
		       ? "1" : "0");

	if (off + count >= len)
		*eof = 1;
	if (len < off)
		return 0;
	*start = page + off;
	return ((count < len - off) ? count : len - off);
}