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
struct info_str {char* buffer; int length; scalar_t__ offset; scalar_t__ pos; } ;
typedef  scalar_t__ off_t ;
struct TYPE_5__ {int /*<<< orphan*/  Word; } ;
struct TYPE_6__ {int /*<<< orphan*/  NumberOfPorts; TYPE_1__ FWVersion; } ;
struct TYPE_7__ {int /*<<< orphan*/  req_depth; TYPE_2__ facts; int /*<<< orphan*/  prod_name; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ MPT_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  MPT_FW_REV_MAGIC_ID_STRING ; 
 int /*<<< orphan*/  mptscsih_copy_info (struct info_str*,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
mptscsih_host_info(MPT_ADAPTER *ioc, char *pbuf, off_t offset, int len)
{
	struct info_str info;

	info.buffer	= pbuf;
	info.length	= len;
	info.offset	= offset;
	info.pos	= 0;

	mptscsih_copy_info(&info, "%s: %s, ", ioc->name, ioc->prod_name);
	mptscsih_copy_info(&info, "%s%08xh, ", MPT_FW_REV_MAGIC_ID_STRING, ioc->facts.FWVersion.Word);
	mptscsih_copy_info(&info, "Ports=%d, ", ioc->facts.NumberOfPorts);
	mptscsih_copy_info(&info, "MaxQ=%d\n", ioc->req_depth);

	return ((info.pos > info.offset) ? info.pos - info.offset : 0);
}