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
struct TYPE_2__ {int /*<<< orphan*/  berr; int /*<<< orphan*/  qdio; int /*<<< orphan*/  status; int /*<<< orphan*/  response; } ;
struct zfcp_dbf_hba_record {int /*<<< orphan*/ * tag; TYPE_1__ u; int /*<<< orphan*/ * tag2; } ;
struct debug_view {int dummy; } ;
typedef  int /*<<< orphan*/  debug_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_DBF_TAG_SIZE ; 
 scalar_t__ isalpha (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_dbf_hba_view_berr (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_dbf_hba_view_qdio (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_dbf_hba_view_response (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_dbf_hba_view_status (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_dbf_tag (char**,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int zfcp_dbf_hba_view_format(debug_info_t *id, struct debug_view *view,
				    char *out_buf, const char *in_buf)
{
	struct zfcp_dbf_hba_record *r = (struct zfcp_dbf_hba_record *)in_buf;
	char *p = out_buf;

	if (strncmp(r->tag, "dump", ZFCP_DBF_TAG_SIZE) == 0)
		return 0;

	zfcp_dbf_tag(&p, "tag", r->tag);
	if (isalpha(r->tag2[0]))
		zfcp_dbf_tag(&p, "tag2", r->tag2);

	if (strncmp(r->tag, "resp", ZFCP_DBF_TAG_SIZE) == 0)
		zfcp_dbf_hba_view_response(&p, &r->u.response);
	else if (strncmp(r->tag, "stat", ZFCP_DBF_TAG_SIZE) == 0)
		zfcp_dbf_hba_view_status(&p, &r->u.status);
	else if (strncmp(r->tag, "qdio", ZFCP_DBF_TAG_SIZE) == 0)
		zfcp_dbf_hba_view_qdio(&p, &r->u.qdio);
	else if (strncmp(r->tag, "berr", ZFCP_DBF_TAG_SIZE) == 0)
		zfcp_dbf_hba_view_berr(&p, &r->u.berr);

	if (strncmp(r->tag, "resp", ZFCP_DBF_TAG_SIZE) != 0)
		p += sprintf(p, "\n");
	return p - out_buf;
}