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
typedef  enum i2400m_brh_opcode { ____Placeholder_i2400m_brh_opcode } i2400m_brh_opcode ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int I2400M_BRH_DIRECT_ACCESS ; 
 int I2400M_BRH_OPCODE_MASK ; 
 int I2400M_BRH_RESPONSE_REQUIRED ; 
 int I2400M_BRH_SIGNATURE ; 
 int I2400M_BRH_USE_CHECKSUM ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static inline
__le32 i2400m_brh_command(enum i2400m_brh_opcode opcode, unsigned use_checksum,
			  unsigned direct_access)
{
	return cpu_to_le32(
		I2400M_BRH_SIGNATURE
		| (direct_access ? I2400M_BRH_DIRECT_ACCESS : 0)
		| I2400M_BRH_RESPONSE_REQUIRED /* response always required */
		| (use_checksum ? I2400M_BRH_USE_CHECKSUM : 0)
		| (opcode & I2400M_BRH_OPCODE_MASK));
}