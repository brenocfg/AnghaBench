#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pos; scalar_t__ offset; scalar_t__ localpos; scalar_t__ length; int buffer; } ;
typedef  TYPE_1__ IPS_INFOSTR ;

/* Variables and functions */
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int /*<<< orphan*/  memcpy (int,char*,int) ; 

__attribute__((used)) static void
copy_mem_info(IPS_INFOSTR * info, char *data, int len)
{
	METHOD_TRACE("copy_mem_info", 1);

	if (info->pos + len < info->offset) {
		info->pos += len;
		return;
	}

	if (info->pos < info->offset) {
		data += (info->offset - info->pos);
		len -= (info->offset - info->pos);
		info->pos += (info->offset - info->pos);
	}

	if (info->localpos + len > info->length)
		len = info->length - info->localpos;

	if (len > 0) {
		memcpy(info->buffer + info->localpos, data, len);
		info->pos += len;
		info->localpos += len;
	}
}