#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct zfcp_unit {TYPE_2__* port; } ;
struct scsi_cmnd {int dummy; } ;
struct TYPE_4__ {TYPE_1__* adapter; } ;
struct TYPE_3__ {int /*<<< orphan*/  dbf; } ;

/* Variables and functions */
 scalar_t__ FCP_TMF_TGT_RESET ; 
 int /*<<< orphan*/  zfcp_dbf_scsi (char*,char const*,int,int /*<<< orphan*/ ,struct scsi_cmnd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void zfcp_dbf_scsi_devreset(const char *tag, u8 flag, struct zfcp_unit *unit,
			    struct scsi_cmnd *scsi_cmnd)
{
	zfcp_dbf_scsi(flag == FCP_TMF_TGT_RESET ? "trst" : "lrst", tag, 1,
			    unit->port->adapter->dbf, scsi_cmnd, NULL, 0);
}