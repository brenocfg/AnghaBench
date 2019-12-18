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
struct isp1301 {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline int
isp1301_set_bits(struct isp1301 *isp, u8 reg, u8 bits)
{
	return i2c_smbus_write_byte_data(isp->client, reg + 0, bits);
}