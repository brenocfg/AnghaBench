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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct ixgbe_hw {int dummy; } ;
struct ixgbe_hic_hdr {scalar_t__ buf_len; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_ERR_HOST_INTERFACE_COMMAND ; 
 int /*<<< orphan*/  IXGBE_FLEX_MNG ; 
 int /*<<< orphan*/  IXGBE_HICR ; 
 scalar_t__ IXGBE_HICR_C ; 
 scalar_t__ IXGBE_HICR_EN ; 
 scalar_t__ IXGBE_HICR_SV ; 
 scalar_t__ IXGBE_HI_COMMAND_TIMEOUT ; 
 scalar_t__ IXGBE_HI_MAX_BLOCK_BYTE_LENGTH ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ IXGBE_READ_REG_ARRAY (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG_ARRAY (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 int /*<<< orphan*/  le32_to_cpus (scalar_t__*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static s32 ixgbe_host_interface_command(struct ixgbe_hw *hw, u32 *buffer,
					u32 length)
{
	u32 hicr, i, bi;
	u32 hdr_size = sizeof(struct ixgbe_hic_hdr);
	u8 buf_len, dword_len;

	s32 ret_val = 0;

	if (length == 0 || length & 0x3 ||
	    length > IXGBE_HI_MAX_BLOCK_BYTE_LENGTH) {
		hw_dbg(hw, "Buffer length failure.\n");
		ret_val = IXGBE_ERR_HOST_INTERFACE_COMMAND;
		goto out;
	}

	/* Check that the host interface is enabled. */
	hicr = IXGBE_READ_REG(hw, IXGBE_HICR);
	if ((hicr & IXGBE_HICR_EN) == 0) {
		hw_dbg(hw, "IXGBE_HOST_EN bit disabled.\n");
		ret_val = IXGBE_ERR_HOST_INTERFACE_COMMAND;
		goto out;
	}

	/* Calculate length in DWORDs */
	dword_len = length >> 2;

	/*
	 * The device driver writes the relevant command block
	 * into the ram area.
	 */
	for (i = 0; i < dword_len; i++)
		IXGBE_WRITE_REG_ARRAY(hw, IXGBE_FLEX_MNG,
				      i, cpu_to_le32(buffer[i]));

	/* Setting this bit tells the ARC that a new command is pending. */
	IXGBE_WRITE_REG(hw, IXGBE_HICR, hicr | IXGBE_HICR_C);

	for (i = 0; i < IXGBE_HI_COMMAND_TIMEOUT; i++) {
		hicr = IXGBE_READ_REG(hw, IXGBE_HICR);
		if (!(hicr & IXGBE_HICR_C))
			break;
		usleep_range(1000, 2000);
	}

	/* Check command successful completion. */
	if (i == IXGBE_HI_COMMAND_TIMEOUT ||
	    (!(IXGBE_READ_REG(hw, IXGBE_HICR) & IXGBE_HICR_SV))) {
		hw_dbg(hw, "Command has failed with no status valid.\n");
		ret_val = IXGBE_ERR_HOST_INTERFACE_COMMAND;
		goto out;
	}

	/* Calculate length in DWORDs */
	dword_len = hdr_size >> 2;

	/* first pull in the header so we know the buffer length */
	for (bi = 0; bi < dword_len; bi++) {
		buffer[bi] = IXGBE_READ_REG_ARRAY(hw, IXGBE_FLEX_MNG, bi);
		le32_to_cpus(&buffer[bi]);
	}

	/* If there is any thing in data position pull it in */
	buf_len = ((struct ixgbe_hic_hdr *)buffer)->buf_len;
	if (buf_len == 0)
		goto out;

	if (length < (buf_len + hdr_size)) {
		hw_dbg(hw, "Buffer not large enough for reply message.\n");
		ret_val = IXGBE_ERR_HOST_INTERFACE_COMMAND;
		goto out;
	}

	/* Calculate length in DWORDs, add 3 for odd lengths */
	dword_len = (buf_len + 3) >> 2;

	/* Pull in the rest of the buffer (bi is where we left off)*/
	for (; bi <= dword_len; bi++) {
		buffer[bi] = IXGBE_READ_REG_ARRAY(hw, IXGBE_FLEX_MNG, bi);
		le32_to_cpus(&buffer[bi]);
	}

out:
	return ret_val;
}