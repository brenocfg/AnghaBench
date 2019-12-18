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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct be_dma_mem {int dummy; } ;
struct be_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  data_len_cmd ;

/* Variables and functions */
 int lancer_cmd_read_object (struct be_adapter*,struct be_dma_mem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct be_dma_mem*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32
lancer_cmd_get_file_len(struct be_adapter *adapter, u8 *file_name)
{
	u32 data_read = 0, eof;
	u8 addn_status;
	struct be_dma_mem data_len_cmd;
	int status;

	memset(&data_len_cmd, 0, sizeof(data_len_cmd));
	/* data_offset and data_size should be 0 to get reg len */
	status = lancer_cmd_read_object(adapter, &data_len_cmd, 0, 0,
				file_name, &data_read, &eof, &addn_status);

	return data_read;
}