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
typedef  int /*<<< orphan*/  u16 ;
struct sta_id_modify {int dummy; } ;
struct il_addsta_cmd {int /*<<< orphan*/  add_immediate_ba_ssn; int /*<<< orphan*/  remove_immediate_ba_tid; int /*<<< orphan*/  add_immediate_ba_tid; int /*<<< orphan*/  rate_n_flags; int /*<<< orphan*/  station_flags_msk; int /*<<< orphan*/  station_flags; int /*<<< orphan*/  key; int /*<<< orphan*/  sta; int /*<<< orphan*/  mode; } ;
struct il4965_keyinfo {int dummy; } ;
struct il3945_addsta_cmd {int /*<<< orphan*/  add_immediate_ba_ssn; int /*<<< orphan*/  remove_immediate_ba_tid; int /*<<< orphan*/  add_immediate_ba_tid; int /*<<< orphan*/  rate_n_flags; int /*<<< orphan*/  tid_disable_tx; int /*<<< orphan*/  station_flags_msk; int /*<<< orphan*/  station_flags; int /*<<< orphan*/  key; int /*<<< orphan*/  sta; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u16
il3945_build_addsta_hcmd(const struct il_addsta_cmd *cmd, u8 * data)
{
	struct il3945_addsta_cmd *addsta = (struct il3945_addsta_cmd *)data;
	addsta->mode = cmd->mode;
	memcpy(&addsta->sta, &cmd->sta, sizeof(struct sta_id_modify));
	memcpy(&addsta->key, &cmd->key, sizeof(struct il4965_keyinfo));
	addsta->station_flags = cmd->station_flags;
	addsta->station_flags_msk = cmd->station_flags_msk;
	addsta->tid_disable_tx = cpu_to_le16(0);
	addsta->rate_n_flags = cmd->rate_n_flags;
	addsta->add_immediate_ba_tid = cmd->add_immediate_ba_tid;
	addsta->remove_immediate_ba_tid = cmd->remove_immediate_ba_tid;
	addsta->add_immediate_ba_ssn = cmd->add_immediate_ba_ssn;

	return (u16) sizeof(struct il3945_addsta_cmd);
}