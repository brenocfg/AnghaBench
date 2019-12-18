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
struct ipw_sys_config {int accept_non_directed_frames; int disable_unicast_decryption; int disable_multicast_decryption; int pass_noise_stats_to_host; int silence_threshold; scalar_t__ bt_coexist_collision_thr; scalar_t__ enable_cts_to_self; scalar_t__ dot11g_auto_detection; scalar_t__ pass_crc_to_host; scalar_t__ antenna_diversity; scalar_t__ exclude_multicast_unencrypted; scalar_t__ exclude_unicast_unencrypted; scalar_t__ accept_all_data_frames; scalar_t__ answer_broadcast_ssid_probe; scalar_t__ bt_coexistence; } ;

/* Variables and functions */
 scalar_t__ CFG_SYS_ANTENNA_B ; 
 scalar_t__ CFG_SYS_ANTENNA_BOTH ; 
 scalar_t__ antenna ; 
 int /*<<< orphan*/  memset (struct ipw_sys_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static  void init_sys_config(struct ipw_sys_config *sys_config)
{
	memset(sys_config, 0, sizeof(struct ipw_sys_config));
	sys_config->bt_coexistence = 0;
	sys_config->answer_broadcast_ssid_probe = 0;
	sys_config->accept_all_data_frames = 0;
	sys_config->accept_non_directed_frames = 1;
	sys_config->exclude_unicast_unencrypted = 0;
	sys_config->disable_unicast_decryption = 1;
	sys_config->exclude_multicast_unencrypted = 0;
	sys_config->disable_multicast_decryption = 1;
	if (antenna < CFG_SYS_ANTENNA_BOTH || antenna > CFG_SYS_ANTENNA_B)
		antenna = CFG_SYS_ANTENNA_BOTH;
	sys_config->antenna_diversity = antenna;
	sys_config->pass_crc_to_host = 0;	/* TODO: See if 1 gives us FCS */
	sys_config->dot11g_auto_detection = 0;
	sys_config->enable_cts_to_self = 0;
	sys_config->bt_coexist_collision_thr = 0;
	sys_config->pass_noise_stats_to_host = 1;	/* 1 -- fix for 256 */
	sys_config->silence_threshold = 0x1e;
}