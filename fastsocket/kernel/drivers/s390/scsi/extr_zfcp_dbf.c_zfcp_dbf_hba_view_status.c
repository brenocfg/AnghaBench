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
struct zfcp_dbf_hba_record_status {int payload_size; int /*<<< orphan*/  payload; int /*<<< orphan*/  queue_designator; int /*<<< orphan*/  status_subtype; int /*<<< orphan*/  status_type; int /*<<< orphan*/  failed; } ;
struct fsf_queue_designator {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfcp_dbf_out (char**,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_dbf_outd (char**,char*,char*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void zfcp_dbf_hba_view_status(char **p,
				     struct zfcp_dbf_hba_record_status *r)
{
	zfcp_dbf_out(p, "failed", "0x%02x", r->failed);
	zfcp_dbf_out(p, "status_type", "0x%08x", r->status_type);
	zfcp_dbf_out(p, "status_subtype", "0x%08x", r->status_subtype);
	zfcp_dbf_outd(p, "queue_designator", (char *)&r->queue_designator,
		      sizeof(struct fsf_queue_designator), 0,
		      sizeof(struct fsf_queue_designator));
	zfcp_dbf_outd(p, "payload", (char *)&r->payload, r->payload_size, 0,
		      r->payload_size);
}