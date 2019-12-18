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
struct zfcp_dbf_hba_record_qdio {int /*<<< orphan*/  scount; int /*<<< orphan*/  fsf_reqid; int /*<<< orphan*/  sbal_count; int /*<<< orphan*/  sbal_index; int /*<<< orphan*/  qdio_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfcp_dbf_out (char**,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zfcp_dbf_hba_view_qdio(char **p, struct zfcp_dbf_hba_record_qdio *r)
{
	zfcp_dbf_out(p, "qdio_error", "0x%08x", r->qdio_error);
	zfcp_dbf_out(p, "sbal_index", "0x%02x", r->sbal_index);
	zfcp_dbf_out(p, "sbal_count", "0x%02x", r->sbal_count);
	zfcp_dbf_out(p, "fsf_reqid", "0x%0Lx", r->fsf_reqid);
	zfcp_dbf_out(p, "scount", "0x%02x", r->scount);
}