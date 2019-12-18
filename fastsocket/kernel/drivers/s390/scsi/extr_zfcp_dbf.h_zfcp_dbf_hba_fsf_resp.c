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
struct zfcp_fsf_req {int dummy; } ;
struct zfcp_dbf {TYPE_1__* hba; } ;
struct TYPE_2__ {int level; } ;

/* Variables and functions */
 int /*<<< orphan*/  _zfcp_dbf_hba_fsf_response (char const*,int,struct zfcp_fsf_req*,struct zfcp_dbf*) ; 

__attribute__((used)) static inline
void zfcp_dbf_hba_fsf_resp(const char *tag2, int level,
			   struct zfcp_fsf_req *req, struct zfcp_dbf *dbf)
{
	if (level <= dbf->hba->level)
		_zfcp_dbf_hba_fsf_response(tag2, level, req, dbf);
}