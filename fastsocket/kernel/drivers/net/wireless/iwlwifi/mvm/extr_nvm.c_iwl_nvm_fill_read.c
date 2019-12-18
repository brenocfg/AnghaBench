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
typedef  int /*<<< orphan*/  u16 ;
struct iwl_nvm_access_cmd {void* type; void* length; void* offset; } ;

/* Variables and functions */
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void iwl_nvm_fill_read(struct iwl_nvm_access_cmd *cmd,
				     u16 offset, u16 length, u16 section)
{
	cmd->offset = cpu_to_le16(offset);
	cmd->length = cpu_to_le16(length);
	cmd->type = cpu_to_le16(section);
}