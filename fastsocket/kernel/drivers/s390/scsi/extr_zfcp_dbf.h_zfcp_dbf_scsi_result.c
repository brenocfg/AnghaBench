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
struct zfcp_fsf_req {int dummy; } ;
struct zfcp_dbf {int dummy; } ;
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfcp_dbf_scsi (char*,char const*,int,struct zfcp_dbf*,struct scsi_cmnd*,struct zfcp_fsf_req*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void zfcp_dbf_scsi_result(const char *tag, int level, struct zfcp_dbf *dbf,
			  struct scsi_cmnd *scmd, struct zfcp_fsf_req *fsf_req)
{
	zfcp_dbf_scsi("rslt", tag, level, dbf, scmd, fsf_req, 0);
}