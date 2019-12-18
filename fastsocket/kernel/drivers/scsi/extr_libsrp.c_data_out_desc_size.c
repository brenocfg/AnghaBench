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
typedef  int u8 ;
struct srp_indirect_buf {int dummy; } ;
struct srp_direct_buf {int dummy; } ;
struct srp_cmd {int buf_fmt; int data_out_desc_cnt; } ;

/* Variables and functions */
#define  SRP_DATA_DESC_DIRECT 130 
#define  SRP_DATA_DESC_INDIRECT 129 
#define  SRP_NO_DATA_DESC 128 
 int /*<<< orphan*/  eprintk (char*,int) ; 

__attribute__((used)) static int data_out_desc_size(struct srp_cmd *cmd)
{
	int size = 0;
	u8 fmt = cmd->buf_fmt >> 4;

	switch (fmt) {
	case SRP_NO_DATA_DESC:
		break;
	case SRP_DATA_DESC_DIRECT:
		size = sizeof(struct srp_direct_buf);
		break;
	case SRP_DATA_DESC_INDIRECT:
		size = sizeof(struct srp_indirect_buf) +
			sizeof(struct srp_direct_buf) * cmd->data_out_desc_cnt;
		break;
	default:
		eprintk("client error. Invalid data_out_format %x\n", fmt);
		break;
	}
	return size;
}