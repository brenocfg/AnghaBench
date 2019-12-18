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
struct zfcp_dbf_hba_record {int /*<<< orphan*/  tag2; int /*<<< orphan*/  tag; } ;
struct zfcp_dbf {int /*<<< orphan*/  hba_lock; int /*<<< orphan*/  hba; struct zfcp_dbf_hba_record hba_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_DBF_TAG_SIZE ; 
 int /*<<< orphan*/  debug_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct zfcp_dbf_hba_record*,int) ; 
 int /*<<< orphan*/  memset (struct zfcp_dbf_hba_record*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void zfcp_dbf_hba_base(struct zfcp_dbf *dbf, char *tag2)
{
	struct zfcp_dbf_hba_record *r = &dbf->hba_buf;
	unsigned long flags;

	spin_lock_irqsave(&dbf->hba_lock, flags);
	memset(r, 0, sizeof(*r));
	strncpy(r->tag, "base", ZFCP_DBF_TAG_SIZE);
	strncpy(r->tag2, tag2, ZFCP_DBF_TAG_SIZE);
	debug_event(dbf->hba, 0, r, sizeof(*r));
	spin_unlock_irqrestore(&dbf->hba_lock, flags);
}