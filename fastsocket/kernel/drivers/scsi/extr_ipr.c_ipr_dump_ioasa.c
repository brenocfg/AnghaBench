#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct ipr_resource_entry {int dummy; } ;
struct ipr_ioasa64 {int dummy; } ;
struct TYPE_5__ {scalar_t__ ilid; int /*<<< orphan*/  ret_stat_len; int /*<<< orphan*/  fd_ioasc; int /*<<< orphan*/  ioasc; } ;
struct ipr_ioasa {TYPE_2__ hdr; } ;
struct ipr_ioa_cfg {scalar_t__ log_level; scalar_t__ sis64; } ;
struct TYPE_4__ {struct ipr_ioasa ioasa; } ;
struct ipr_cmnd {TYPE_1__ s; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_6__ {scalar_t__ log_ioasa; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 scalar_t__ IPR_DEFAULT_LOG_LEVEL ; 
 int IPR_IOASC_BUS_WAS_RESET ; 
 int IPR_IOASC_IOASC_MASK ; 
 scalar_t__ IPR_MAX_LOG_LEVEL ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_err (char*,...) ; 
 TYPE_3__* ipr_error_table ; 
 int ipr_get_error (int) ; 
 int /*<<< orphan*/  ipr_is_gscsi (struct ipr_resource_entry*) ; 
 int /*<<< orphan*/  ipr_res_err (struct ipr_ioa_cfg*,struct ipr_resource_entry*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipr_dump_ioasa(struct ipr_ioa_cfg *ioa_cfg,
			   struct ipr_cmnd *ipr_cmd, struct ipr_resource_entry *res)
{
	int i;
	u16 data_len;
	u32 ioasc, fd_ioasc;
	struct ipr_ioasa *ioasa = &ipr_cmd->s.ioasa;
	__be32 *ioasa_data = (__be32 *)ioasa;
	int error_index;

	ioasc = be32_to_cpu(ioasa->hdr.ioasc) & IPR_IOASC_IOASC_MASK;
	fd_ioasc = be32_to_cpu(ioasa->hdr.fd_ioasc) & IPR_IOASC_IOASC_MASK;

	if (0 == ioasc)
		return;

	if (ioa_cfg->log_level < IPR_DEFAULT_LOG_LEVEL)
		return;

	if (ioasc == IPR_IOASC_BUS_WAS_RESET && fd_ioasc)
		error_index = ipr_get_error(fd_ioasc);
	else
		error_index = ipr_get_error(ioasc);

	if (ioa_cfg->log_level < IPR_MAX_LOG_LEVEL) {
		/* Don't log an error if the IOA already logged one */
		if (ioasa->hdr.ilid != 0)
			return;

		if (!ipr_is_gscsi(res))
			return;

		if (ipr_error_table[error_index].log_ioasa == 0)
			return;
	}

	ipr_res_err(ioa_cfg, res, "%s\n", ipr_error_table[error_index].error);

	data_len = be16_to_cpu(ioasa->hdr.ret_stat_len);
	if (ioa_cfg->sis64 && sizeof(struct ipr_ioasa64) < data_len)
		data_len = sizeof(struct ipr_ioasa64);
	else if (!ioa_cfg->sis64 && sizeof(struct ipr_ioasa) < data_len)
		data_len = sizeof(struct ipr_ioasa);

	ipr_err("IOASA Dump:\n");

	for (i = 0; i < data_len / 4; i += 4) {
		ipr_err("%08X: %08X %08X %08X %08X\n", i*4,
			be32_to_cpu(ioasa_data[i]),
			be32_to_cpu(ioasa_data[i+1]),
			be32_to_cpu(ioasa_data[i+2]),
			be32_to_cpu(ioasa_data[i+3]));
	}
}