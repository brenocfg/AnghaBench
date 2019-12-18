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
struct ds2482_data {int /*<<< orphan*/  read_prt; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 scalar_t__ DS2482_CMD_WRITE_CONFIG ; 
 int /*<<< orphan*/  DS2482_PTR_CODE_CONFIG ; 
 int /*<<< orphan*/  DS2482_PTR_CODE_STATUS ; 
 scalar_t__ i2c_smbus_write_byte_data (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline int ds2482_send_cmd_data(struct ds2482_data *pdev,
				       u8 cmd, u8 byte)
{
	if (i2c_smbus_write_byte_data(pdev->client, cmd, byte) < 0)
		return -1;

	/* all cmds leave in STATUS, except CONFIG */
	pdev->read_prt = (cmd != DS2482_CMD_WRITE_CONFIG) ?
			 DS2482_PTR_CODE_STATUS : DS2482_PTR_CODE_CONFIG;
	return 0;
}