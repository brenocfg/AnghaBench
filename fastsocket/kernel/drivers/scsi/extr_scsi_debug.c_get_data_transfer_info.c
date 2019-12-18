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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
#define  READ_10 139 
#define  READ_12 138 
#define  READ_16 137 
#define  READ_6 136 
#define  VARIABLE_LENGTH_CMD 135 
#define  WRITE_10 134 
#define  WRITE_12 133 
#define  WRITE_16 132 
#define  WRITE_6 131 
#define  WRITE_SAME 130 
#define  WRITE_SAME_16 129 
#define  XDWRITEREAD_10 128 

__attribute__((used)) static void get_data_transfer_info(unsigned char *cmd,
				   unsigned long long *lba, unsigned int *num,
				   u32 *ei_lba)
{
	*ei_lba = 0;

	switch (*cmd) {
	case VARIABLE_LENGTH_CMD:
		*lba = (u64)cmd[19] | (u64)cmd[18] << 8 |
			(u64)cmd[17] << 16 | (u64)cmd[16] << 24 |
			(u64)cmd[15] << 32 | (u64)cmd[14] << 40 |
			(u64)cmd[13] << 48 | (u64)cmd[12] << 56;

		*ei_lba = (u32)cmd[23] | (u32)cmd[22] << 8 |
			(u32)cmd[21] << 16 | (u32)cmd[20] << 24;

		*num = (u32)cmd[31] | (u32)cmd[30] << 8 | (u32)cmd[29] << 16 |
			(u32)cmd[28] << 24;
		break;

	case WRITE_SAME_16:
	case WRITE_16:
	case READ_16:
		*lba = (u64)cmd[9] | (u64)cmd[8] << 8 |
			(u64)cmd[7] << 16 | (u64)cmd[6] << 24 |
			(u64)cmd[5] << 32 | (u64)cmd[4] << 40 |
			(u64)cmd[3] << 48 | (u64)cmd[2] << 56;

		*num = (u32)cmd[13] | (u32)cmd[12] << 8 | (u32)cmd[11] << 16 |
			(u32)cmd[10] << 24;
		break;
	case WRITE_12:
	case READ_12:
		*lba = (u32)cmd[5] | (u32)cmd[4] << 8 | (u32)cmd[3] << 16 |
			(u32)cmd[2] << 24;

		*num = (u32)cmd[9] | (u32)cmd[8] << 8 | (u32)cmd[7] << 16 |
			(u32)cmd[6] << 24;
		break;
	case WRITE_SAME:
	case WRITE_10:
	case READ_10:
	case XDWRITEREAD_10:
		*lba = (u32)cmd[5] | (u32)cmd[4] << 8 |	(u32)cmd[3] << 16 |
			(u32)cmd[2] << 24;

		*num = (u32)cmd[8] | (u32)cmd[7] << 8;
		break;
	case WRITE_6:
	case READ_6:
		*lba = (u32)cmd[3] | (u32)cmd[2] << 8 |
			(u32)(cmd[1] & 0x1f) << 16;
		*num = (0 == cmd[4]) ? 256 : cmd[4];
		break;
	default:
		break;
	}
}