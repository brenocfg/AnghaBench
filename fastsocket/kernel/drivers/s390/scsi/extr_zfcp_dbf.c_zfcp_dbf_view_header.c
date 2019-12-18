#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct zfcp_dbf_dump {scalar_t__ size; scalar_t__ offset; scalar_t__ total_size; int /*<<< orphan*/  data; int /*<<< orphan*/  tag; } ;
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct debug_view {int dummy; } ;
typedef  int /*<<< orphan*/  debug_info_t ;
struct TYPE_6__ {int /*<<< orphan*/  cpuid; } ;
struct TYPE_7__ {TYPE_1__ fields; int /*<<< orphan*/  stck; } ;
struct TYPE_8__ {TYPE_2__ id; } ;
typedef  TYPE_3__ debug_entry_t ;

/* Variables and functions */
 scalar_t__ DEBUG_DATA (TYPE_3__*) ; 
 int /*<<< orphan*/  ZFCP_DBF_TAG_SIZE ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 int /*<<< orphan*/  stck_to_timespec (int /*<<< orphan*/ ,struct timespec*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_dbf_out (char**,char*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  zfcp_dbf_outd (char**,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int zfcp_dbf_view_header(debug_info_t *id, struct debug_view *view,
				int area, debug_entry_t *entry, char *out_buf)
{
	struct zfcp_dbf_dump *dump = (struct zfcp_dbf_dump *)DEBUG_DATA(entry);
	struct timespec t;
	char *p = out_buf;

	if (strncmp(dump->tag, "dump", ZFCP_DBF_TAG_SIZE) != 0) {
		stck_to_timespec(entry->id.stck, &t);
		zfcp_dbf_out(&p, "timestamp", "%011lu:%06lu",
			     t.tv_sec, t.tv_nsec);
		zfcp_dbf_out(&p, "cpu", "%02i", entry->id.fields.cpuid);
	} else	{
		zfcp_dbf_outd(&p, "", dump->data, dump->size, dump->offset,
			      dump->total_size);
		if ((dump->offset + dump->size) == dump->total_size)
			p += sprintf(p, "\n");
	}
	return p - out_buf;
}