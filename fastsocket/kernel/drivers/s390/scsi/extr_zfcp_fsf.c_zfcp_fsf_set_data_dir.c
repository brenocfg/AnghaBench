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
typedef  int /*<<< orphan*/  u32 ;
struct scsi_cmnd {int /*<<< orphan*/  sc_data_direction; } ;

/* Variables and functions */
#define  DMA_BIDIRECTIONAL 136 
#define  DMA_FROM_DEVICE 135 
#define  DMA_NONE 134 
#define  DMA_TO_DEVICE 133 
 int EINVAL ; 
 int /*<<< orphan*/  FSF_DATADIR_CMND ; 
 int /*<<< orphan*/  FSF_DATADIR_DIF_READ_CONVERT ; 
 int /*<<< orphan*/  FSF_DATADIR_DIF_READ_STRIP ; 
 int /*<<< orphan*/  FSF_DATADIR_DIF_WRITE_CONVERT ; 
 int /*<<< orphan*/  FSF_DATADIR_DIF_WRITE_INSERT ; 
 int /*<<< orphan*/  FSF_DATADIR_READ ; 
 int /*<<< orphan*/  FSF_DATADIR_WRITE ; 
#define  SCSI_PROT_NORMAL 132 
#define  SCSI_PROT_READ_PASS 131 
#define  SCSI_PROT_READ_STRIP 130 
#define  SCSI_PROT_WRITE_INSERT 129 
#define  SCSI_PROT_WRITE_PASS 128 
 int scsi_get_prot_op (struct scsi_cmnd*) ; 

__attribute__((used)) static int zfcp_fsf_set_data_dir(struct scsi_cmnd *scsi_cmnd, u32 *data_dir)
{
	switch (scsi_get_prot_op(scsi_cmnd)) {
	case SCSI_PROT_NORMAL:
		switch (scsi_cmnd->sc_data_direction) {
		case DMA_NONE:
			*data_dir = FSF_DATADIR_CMND;
			break;
		case DMA_FROM_DEVICE:
			*data_dir = FSF_DATADIR_READ;
			break;
		case DMA_TO_DEVICE:
			*data_dir = FSF_DATADIR_WRITE;
			break;
		case DMA_BIDIRECTIONAL:
			return -EINVAL;
		}
		break;

	case SCSI_PROT_READ_STRIP:
		*data_dir = FSF_DATADIR_DIF_READ_STRIP;
		break;
	case SCSI_PROT_WRITE_INSERT:
		*data_dir = FSF_DATADIR_DIF_WRITE_INSERT;
		break;
	case SCSI_PROT_READ_PASS:
		*data_dir = FSF_DATADIR_DIF_READ_CONVERT;
		break;
	case SCSI_PROT_WRITE_PASS:
		*data_dir = FSF_DATADIR_DIF_WRITE_CONVERT;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}