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
typedef  int /*<<< orphan*/  u32 ;
struct qla_hw_data {scalar_t__ fw_type; TYPE_2__* hablob; } ;
struct qla82xx_uri_data_desc {int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_4__ {TYPE_1__* fw; } ;
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 size_t FW_SIZE_OFFSET ; 
 scalar_t__ QLA82XX_UNIFIED_ROMIMAGE ; 
 int /*<<< orphan*/  QLA82XX_URI_DIR_SECT_FW ; 
 int /*<<< orphan*/  QLA82XX_URI_FIRMWARE_IDX_OFF ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct qla82xx_uri_data_desc* qla82xx_get_data_desc (struct qla_hw_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __le32
qla82xx_get_fw_size(struct qla_hw_data *ha)
{
	struct qla82xx_uri_data_desc *uri_desc = NULL;

	if (ha->fw_type == QLA82XX_UNIFIED_ROMIMAGE) {
		uri_desc =  qla82xx_get_data_desc(ha, QLA82XX_URI_DIR_SECT_FW,
		    QLA82XX_URI_FIRMWARE_IDX_OFF);
		if (uri_desc)
			return cpu_to_le32(uri_desc->size);
	}

	return cpu_to_le32(*(u32 *)&ha->hablob->fw->data[FW_SIZE_OFFSET]);
}