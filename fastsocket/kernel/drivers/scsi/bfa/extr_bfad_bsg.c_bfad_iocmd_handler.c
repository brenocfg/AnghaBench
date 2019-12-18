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
struct bfad_s {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IOCMD_ADAPTER_CFG_MODE 251 
#define  IOCMD_BOOT_CFG 250 
#define  IOCMD_BOOT_QUERY 249 
#define  IOCMD_CEE_GET_ATTR 248 
#define  IOCMD_CEE_GET_STATS 247 
#define  IOCMD_CEE_RESET_STATS 246 
#define  IOCMD_DEBUG_FW_CORE 245 
#define  IOCMD_DEBUG_FW_STATE_CLR 244 
#define  IOCMD_DEBUG_PORTLOG 243 
#define  IOCMD_DEBUG_PORTLOG_CLR 242 
#define  IOCMD_DEBUG_PORTLOG_CTL 241 
#define  IOCMD_DEBUG_START_DTRC 240 
#define  IOCMD_DEBUG_STOP_DTRC 239 
#define  IOCMD_DIAG_BEACON_LPORT 238 
#define  IOCMD_DIAG_DPORT_DISABLE 237 
#define  IOCMD_DIAG_DPORT_ENABLE 236 
#define  IOCMD_DIAG_DPORT_SHOW 235 
#define  IOCMD_DIAG_DPORT_START 234 
#define  IOCMD_DIAG_FWPING 233 
#define  IOCMD_DIAG_LB_STAT 232 
#define  IOCMD_DIAG_LED 231 
#define  IOCMD_DIAG_LOOPBACK 230 
#define  IOCMD_DIAG_MEMTEST 229 
#define  IOCMD_DIAG_QUEUETEST 228 
#define  IOCMD_DIAG_SFP 227 
#define  IOCMD_DIAG_TEMP 226 
#define  IOCMD_ETHBOOT_CFG 225 
#define  IOCMD_ETHBOOT_QUERY 224 
#define  IOCMD_FAA_QUERY 223 
#define  IOCMD_FABRIC_GET_LPORTS 222 
#define  IOCMD_FCPIM_DEL_ITN_STATS 221 
#define  IOCMD_FCPIM_FAILOVER 220 
#define  IOCMD_FCPIM_MODSTATS 219 
#define  IOCMD_FCPIM_MODSTATSCLR 218 
#define  IOCMD_FCPIM_PROFILE_OFF 217 
#define  IOCMD_FCPIM_PROFILE_ON 216 
#define  IOCMD_FCPIM_THROTTLE_QUERY 215 
#define  IOCMD_FCPIM_THROTTLE_SET 214 
#define  IOCMD_FCPORT_DISABLE 213 
#define  IOCMD_FCPORT_ENABLE 212 
#define  IOCMD_FCPORT_GET_STATS 211 
#define  IOCMD_FCPORT_RESET_STATS 210 
#define  IOCMD_FLASH_DISABLE_OPTROM 209 
#define  IOCMD_FLASH_ENABLE_OPTROM 208 
#define  IOCMD_FLASH_ERASE_PART 207 
#define  IOCMD_FLASH_GET_ATTR 206 
#define  IOCMD_FLASH_READ_PART 205 
#define  IOCMD_FLASH_UPDATE_PART 204 
#define  IOCMD_FRUVPD_GET_MAX_SIZE 203 
#define  IOCMD_FRUVPD_READ 202 
#define  IOCMD_FRUVPD_UPDATE 201 
#define  IOCMD_IOCFC_GET_ATTR 200 
#define  IOCMD_IOCFC_SET_INTR 199 
#define  IOCMD_IOC_DISABLE 198 
#define  IOCMD_IOC_ENABLE 197 
#define  IOCMD_IOC_GET_ATTR 196 
#define  IOCMD_IOC_GET_FWSTATS 195 
#define  IOCMD_IOC_GET_INFO 194 
#define  IOCMD_IOC_GET_STATS 193 
#define  IOCMD_IOC_PCIFN_CFG 192 
#define  IOCMD_IOC_RESET_FWSTATS 191 
#define  IOCMD_IOC_RESET_STATS 190 
#define  IOCMD_IOC_SET_ADAPTER_NAME 189 
#define  IOCMD_IOC_SET_PORT_NAME 188 
#define  IOCMD_ITNIM_GET_ATTR 187 
#define  IOCMD_ITNIM_GET_IOPROFILE 186 
#define  IOCMD_ITNIM_GET_IOSTATS 185 
#define  IOCMD_ITNIM_GET_ITNSTATS 184 
#define  IOCMD_ITNIM_RESET_STATS 183 
#define  IOCMD_LPORT_GET_ATTR 182 
#define  IOCMD_LPORT_GET_IOSTATS 181 
#define  IOCMD_LPORT_GET_RPORTS 180 
#define  IOCMD_LPORT_GET_STATS 179 
#define  IOCMD_LPORT_RESET_STATS 178 
#define  IOCMD_PCIFN_BW 177 
#define  IOCMD_PCIFN_CREATE 176 
#define  IOCMD_PCIFN_DELETE 175 
#define  IOCMD_PHY_GET_ATTR 174 
#define  IOCMD_PHY_GET_STATS 173 
#define  IOCMD_PHY_READ_FW 172 
#define  IOCMD_PHY_UPDATE_FW 171 
#define  IOCMD_PORT_BBCR_DISABLE 170 
#define  IOCMD_PORT_BBCR_ENABLE 169 
#define  IOCMD_PORT_BBCR_GET_ATTR 168 
#define  IOCMD_PORT_CFG_ALPA 167 
#define  IOCMD_PORT_CFG_MAXFRSZ 166 
#define  IOCMD_PORT_CFG_MODE 165 
#define  IOCMD_PORT_CFG_SPEED 164 
#define  IOCMD_PORT_CFG_TOPO 163 
#define  IOCMD_PORT_CLR_ALPA 162 
#define  IOCMD_PORT_DISABLE 161 
#define  IOCMD_PORT_ENABLE 160 
#define  IOCMD_PORT_GET_ATTR 159 
#define  IOCMD_PORT_GET_STATS 158 
#define  IOCMD_PORT_RESET_STATS 157 
#define  IOCMD_PREBOOT_QUERY 156 
#define  IOCMD_QOS_DISABLE 155 
#define  IOCMD_QOS_ENABLE 154 
#define  IOCMD_QOS_GET_ATTR 153 
#define  IOCMD_QOS_GET_STATS 152 
#define  IOCMD_QOS_GET_VC_ATTR 151 
#define  IOCMD_QOS_RESET_STATS 150 
#define  IOCMD_QOS_SET_BW 149 
#define  IOCMD_RATELIM_DEF_SPEED 148 
#define  IOCMD_RATELIM_DISABLE 147 
#define  IOCMD_RATELIM_ENABLE 146 
#define  IOCMD_RPORT_GET_ADDR 145 
#define  IOCMD_RPORT_GET_ATTR 144 
#define  IOCMD_RPORT_GET_STATS 143 
#define  IOCMD_RPORT_RESET_STATS 142 
#define  IOCMD_RPORT_SET_SPEED 141 
#define  IOCMD_SFP_MEDIA 140 
#define  IOCMD_SFP_SPEED 139 
#define  IOCMD_TFRU_READ 138 
#define  IOCMD_TFRU_WRITE 137 
#define  IOCMD_TRUNK_DISABLE 136 
#define  IOCMD_TRUNK_ENABLE 135 
#define  IOCMD_TRUNK_GET_ATTR 134 
#define  IOCMD_VF_GET_STATS 133 
#define  IOCMD_VF_RESET_STATS 132 
#define  IOCMD_VHBA_QUERY 131 
#define  IOCMD_VPORT_GET_ATTR 130 
#define  IOCMD_VPORT_GET_STATS 129 
#define  IOCMD_VPORT_RESET_STATS 128 
 int bfad_iocmd_ablk_optrom (struct bfad_s*,unsigned int,void*) ; 
 int bfad_iocmd_adapter_cfg_mode (struct bfad_s*,void*) ; 
 int bfad_iocmd_boot_cfg (struct bfad_s*,void*) ; 
 int bfad_iocmd_boot_query (struct bfad_s*,void*) ; 
 int bfad_iocmd_cee_attr (struct bfad_s*,void*,unsigned int) ; 
 int bfad_iocmd_cee_get_stats (struct bfad_s*,void*,unsigned int) ; 
 int bfad_iocmd_cee_reset_stats (struct bfad_s*,void*) ; 
 int bfad_iocmd_cfg_fcpim (struct bfad_s*,void*) ; 
 int bfad_iocmd_cfg_trunk (struct bfad_s*,void*,unsigned int) ; 
 int bfad_iocmd_debug_ctl (struct bfad_s*,void*,unsigned int) ; 
 int bfad_iocmd_debug_fw_core (struct bfad_s*,void*,unsigned int) ; 
 int bfad_iocmd_diag_beacon_lport (struct bfad_s*,void*) ; 
 int bfad_iocmd_diag_dport_disable (struct bfad_s*,void*) ; 
 int bfad_iocmd_diag_dport_enable (struct bfad_s*,void*) ; 
 int bfad_iocmd_diag_dport_show (struct bfad_s*,void*) ; 
 int bfad_iocmd_diag_dport_start (struct bfad_s*,void*) ; 
 int bfad_iocmd_diag_fwping (struct bfad_s*,void*) ; 
 int bfad_iocmd_diag_lb_stat (struct bfad_s*,void*) ; 
 int bfad_iocmd_diag_led (struct bfad_s*,void*) ; 
 int bfad_iocmd_diag_loopback (struct bfad_s*,void*) ; 
 int bfad_iocmd_diag_memtest (struct bfad_s*,void*) ; 
 int bfad_iocmd_diag_queuetest (struct bfad_s*,void*) ; 
 int bfad_iocmd_diag_sfp (struct bfad_s*,void*) ; 
 int bfad_iocmd_diag_temp (struct bfad_s*,void*) ; 
 int bfad_iocmd_ethboot_cfg (struct bfad_s*,void*) ; 
 int bfad_iocmd_ethboot_query (struct bfad_s*,void*) ; 
 int bfad_iocmd_faa_query (struct bfad_s*,void*) ; 
 int bfad_iocmd_fabric_get_lports (struct bfad_s*,void*,unsigned int) ; 
 int bfad_iocmd_fcpim_cfg_profile (struct bfad_s*,void*,unsigned int) ; 
 int bfad_iocmd_fcpim_clr_modstats (struct bfad_s*,void*) ; 
 int bfad_iocmd_fcpim_get_del_itn_stats (struct bfad_s*,void*) ; 
 int bfad_iocmd_fcpim_get_modstats (struct bfad_s*,void*) ; 
 int bfad_iocmd_fcpim_throttle_query (struct bfad_s*,void*) ; 
 int bfad_iocmd_fcpim_throttle_set (struct bfad_s*,void*) ; 
 int bfad_iocmd_fcport_disable (struct bfad_s*,void*) ; 
 int bfad_iocmd_fcport_enable (struct bfad_s*,void*) ; 
 int bfad_iocmd_fcport_get_stats (struct bfad_s*,void*) ; 
 int bfad_iocmd_fcport_reset_stats (struct bfad_s*,void*) ; 
 int bfad_iocmd_flash_erase_part (struct bfad_s*,void*) ; 
 int bfad_iocmd_flash_get_attr (struct bfad_s*,void*) ; 
 int bfad_iocmd_flash_read_part (struct bfad_s*,void*,unsigned int) ; 
 int bfad_iocmd_flash_update_part (struct bfad_s*,void*,unsigned int) ; 
 int bfad_iocmd_fruvpd_get_max_size (struct bfad_s*,void*) ; 
 int bfad_iocmd_fruvpd_read (struct bfad_s*,void*) ; 
 int bfad_iocmd_fruvpd_update (struct bfad_s*,void*) ; 
 int bfad_iocmd_ioc_disable (struct bfad_s*,void*) ; 
 int bfad_iocmd_ioc_enable (struct bfad_s*,void*) ; 
 int bfad_iocmd_ioc_get_attr (struct bfad_s*,void*) ; 
 int bfad_iocmd_ioc_get_fwstats (struct bfad_s*,void*,unsigned int) ; 
 int bfad_iocmd_ioc_get_info (struct bfad_s*,void*) ; 
 int bfad_iocmd_ioc_get_pcifn_cfg (struct bfad_s*,void*) ; 
 int bfad_iocmd_ioc_get_stats (struct bfad_s*,void*) ; 
 int bfad_iocmd_ioc_reset_stats (struct bfad_s*,void*,unsigned int) ; 
 int bfad_iocmd_ioc_set_name (struct bfad_s*,void*,unsigned int) ; 
 int bfad_iocmd_iocfc_get_attr (struct bfad_s*,void*) ; 
 int bfad_iocmd_iocfc_set_intr (struct bfad_s*,void*) ; 
 int bfad_iocmd_itnim_get_attr (struct bfad_s*,void*) ; 
 int bfad_iocmd_itnim_get_ioprofile (struct bfad_s*,void*) ; 
 int bfad_iocmd_itnim_get_iostats (struct bfad_s*,void*) ; 
 int bfad_iocmd_itnim_get_itnstats (struct bfad_s*,void*) ; 
 int bfad_iocmd_itnim_reset_stats (struct bfad_s*,void*) ; 
 int bfad_iocmd_lport_get_attr (struct bfad_s*,void*) ; 
 int bfad_iocmd_lport_get_iostats (struct bfad_s*,void*) ; 
 int bfad_iocmd_lport_get_rports (struct bfad_s*,void*,unsigned int) ; 
 int bfad_iocmd_lport_get_stats (struct bfad_s*,void*) ; 
 int bfad_iocmd_lport_reset_stats (struct bfad_s*,void*) ; 
 int bfad_iocmd_pcifn_bw (struct bfad_s*,void*) ; 
 int bfad_iocmd_pcifn_create (struct bfad_s*,void*) ; 
 int bfad_iocmd_pcifn_delete (struct bfad_s*,void*) ; 
 int bfad_iocmd_phy_get_attr (struct bfad_s*,void*) ; 
 int bfad_iocmd_phy_get_stats (struct bfad_s*,void*) ; 
 int bfad_iocmd_phy_read (struct bfad_s*,void*,unsigned int) ; 
 int bfad_iocmd_phy_update (struct bfad_s*,void*,unsigned int) ; 
 int bfad_iocmd_porglog_ctl (struct bfad_s*,void*) ; 
 int bfad_iocmd_porglog_get (struct bfad_s*,void*) ; 
 int bfad_iocmd_port_cfg_bbcr (struct bfad_s*,unsigned int,void*) ; 
 int bfad_iocmd_port_cfg_maxfrsize (struct bfad_s*,void*) ; 
 int bfad_iocmd_port_cfg_mode (struct bfad_s*,void*) ; 
 int bfad_iocmd_port_disable (struct bfad_s*,void*) ; 
 int bfad_iocmd_port_enable (struct bfad_s*,void*) ; 
 int bfad_iocmd_port_get_attr (struct bfad_s*,void*) ; 
 int bfad_iocmd_port_get_bbcr_attr (struct bfad_s*,void*) ; 
 int bfad_iocmd_port_get_stats (struct bfad_s*,void*,unsigned int) ; 
 int bfad_iocmd_port_reset_stats (struct bfad_s*,void*) ; 
 int bfad_iocmd_preboot_query (struct bfad_s*,void*) ; 
 int bfad_iocmd_qos (struct bfad_s*,void*,unsigned int) ; 
 int bfad_iocmd_qos_get_attr (struct bfad_s*,void*) ; 
 int bfad_iocmd_qos_get_stats (struct bfad_s*,void*) ; 
 int bfad_iocmd_qos_get_vc_attr (struct bfad_s*,void*) ; 
 int bfad_iocmd_qos_reset_stats (struct bfad_s*,void*) ; 
 int bfad_iocmd_qos_set_bw (struct bfad_s*,void*) ; 
 int bfad_iocmd_ratelim (struct bfad_s*,unsigned int,void*) ; 
 int bfad_iocmd_ratelim_speed (struct bfad_s*,unsigned int,void*) ; 
 int bfad_iocmd_rport_clr_stats (struct bfad_s*,void*) ; 
 int bfad_iocmd_rport_get_addr (struct bfad_s*,void*) ; 
 int bfad_iocmd_rport_get_attr (struct bfad_s*,void*) ; 
 int bfad_iocmd_rport_get_stats (struct bfad_s*,void*) ; 
 int bfad_iocmd_rport_set_speed (struct bfad_s*,void*) ; 
 int bfad_iocmd_set_port_cfg (struct bfad_s*,void*,unsigned int) ; 
 int bfad_iocmd_sfp_media (struct bfad_s*,void*) ; 
 int bfad_iocmd_sfp_speed (struct bfad_s*,void*) ; 
 int bfad_iocmd_tfru_read (struct bfad_s*,void*) ; 
 int bfad_iocmd_tfru_write (struct bfad_s*,void*) ; 
 int bfad_iocmd_trunk_get_attr (struct bfad_s*,void*) ; 
 int bfad_iocmd_vf_clr_stats (struct bfad_s*,void*) ; 
 int bfad_iocmd_vf_get_stats (struct bfad_s*,void*) ; 
 int bfad_iocmd_vhba_query (struct bfad_s*,void*) ; 
 int bfad_iocmd_vport_clr_stats (struct bfad_s*,void*) ; 
 int bfad_iocmd_vport_get_attr (struct bfad_s*,void*) ; 
 int bfad_iocmd_vport_get_stats (struct bfad_s*,void*) ; 

__attribute__((used)) static int
bfad_iocmd_handler(struct bfad_s *bfad, unsigned int cmd, void *iocmd,
		unsigned int payload_len)
{
	int rc = -EINVAL;

	switch (cmd) {
	case IOCMD_IOC_ENABLE:
		rc = bfad_iocmd_ioc_enable(bfad, iocmd);
		break;
	case IOCMD_IOC_DISABLE:
		rc = bfad_iocmd_ioc_disable(bfad, iocmd);
		break;
	case IOCMD_IOC_GET_INFO:
		rc = bfad_iocmd_ioc_get_info(bfad, iocmd);
		break;
	case IOCMD_IOC_GET_ATTR:
		rc = bfad_iocmd_ioc_get_attr(bfad, iocmd);
		break;
	case IOCMD_IOC_GET_STATS:
		rc = bfad_iocmd_ioc_get_stats(bfad, iocmd);
		break;
	case IOCMD_IOC_GET_FWSTATS:
		rc = bfad_iocmd_ioc_get_fwstats(bfad, iocmd, payload_len);
		break;
	case IOCMD_IOC_RESET_STATS:
	case IOCMD_IOC_RESET_FWSTATS:
		rc = bfad_iocmd_ioc_reset_stats(bfad, iocmd, cmd);
		break;
	case IOCMD_IOC_SET_ADAPTER_NAME:
	case IOCMD_IOC_SET_PORT_NAME:
		rc = bfad_iocmd_ioc_set_name(bfad, iocmd, cmd);
		break;
	case IOCMD_IOCFC_GET_ATTR:
		rc = bfad_iocmd_iocfc_get_attr(bfad, iocmd);
		break;
	case IOCMD_IOCFC_SET_INTR:
		rc = bfad_iocmd_iocfc_set_intr(bfad, iocmd);
		break;
	case IOCMD_PORT_ENABLE:
		rc = bfad_iocmd_port_enable(bfad, iocmd);
		break;
	case IOCMD_PORT_DISABLE:
		rc = bfad_iocmd_port_disable(bfad, iocmd);
		break;
	case IOCMD_PORT_GET_ATTR:
		rc = bfad_iocmd_port_get_attr(bfad, iocmd);
		break;
	case IOCMD_PORT_GET_STATS:
		rc = bfad_iocmd_port_get_stats(bfad, iocmd, payload_len);
		break;
	case IOCMD_PORT_RESET_STATS:
		rc = bfad_iocmd_port_reset_stats(bfad, iocmd);
		break;
	case IOCMD_PORT_CFG_TOPO:
	case IOCMD_PORT_CFG_SPEED:
	case IOCMD_PORT_CFG_ALPA:
	case IOCMD_PORT_CLR_ALPA:
		rc = bfad_iocmd_set_port_cfg(bfad, iocmd, cmd);
		break;
	case IOCMD_PORT_CFG_MAXFRSZ:
		rc = bfad_iocmd_port_cfg_maxfrsize(bfad, iocmd);
		break;
	case IOCMD_PORT_BBCR_ENABLE:
	case IOCMD_PORT_BBCR_DISABLE:
		rc = bfad_iocmd_port_cfg_bbcr(bfad, cmd, iocmd);
		break;
	case IOCMD_PORT_BBCR_GET_ATTR:
		rc = bfad_iocmd_port_get_bbcr_attr(bfad, iocmd);
		break;
	case IOCMD_LPORT_GET_ATTR:
		rc = bfad_iocmd_lport_get_attr(bfad, iocmd);
		break;
	case IOCMD_LPORT_GET_STATS:
		rc = bfad_iocmd_lport_get_stats(bfad, iocmd);
		break;
	case IOCMD_LPORT_RESET_STATS:
		rc = bfad_iocmd_lport_reset_stats(bfad, iocmd);
		break;
	case IOCMD_LPORT_GET_IOSTATS:
		rc = bfad_iocmd_lport_get_iostats(bfad, iocmd);
		break;
	case IOCMD_LPORT_GET_RPORTS:
		rc = bfad_iocmd_lport_get_rports(bfad, iocmd, payload_len);
		break;
	case IOCMD_RPORT_GET_ATTR:
		rc = bfad_iocmd_rport_get_attr(bfad, iocmd);
		break;
	case IOCMD_RPORT_GET_ADDR:
		rc = bfad_iocmd_rport_get_addr(bfad, iocmd);
		break;
	case IOCMD_RPORT_GET_STATS:
		rc = bfad_iocmd_rport_get_stats(bfad, iocmd);
		break;
	case IOCMD_RPORT_RESET_STATS:
		rc = bfad_iocmd_rport_clr_stats(bfad, iocmd);
		break;
	case IOCMD_RPORT_SET_SPEED:
		rc = bfad_iocmd_rport_set_speed(bfad, iocmd);
		break;
	case IOCMD_VPORT_GET_ATTR:
		rc = bfad_iocmd_vport_get_attr(bfad, iocmd);
		break;
	case IOCMD_VPORT_GET_STATS:
		rc = bfad_iocmd_vport_get_stats(bfad, iocmd);
		break;
	case IOCMD_VPORT_RESET_STATS:
		rc = bfad_iocmd_vport_clr_stats(bfad, iocmd);
		break;
	case IOCMD_FABRIC_GET_LPORTS:
		rc = bfad_iocmd_fabric_get_lports(bfad, iocmd, payload_len);
		break;
	case IOCMD_RATELIM_ENABLE:
	case IOCMD_RATELIM_DISABLE:
		rc = bfad_iocmd_ratelim(bfad, cmd, iocmd);
		break;
	case IOCMD_RATELIM_DEF_SPEED:
		rc = bfad_iocmd_ratelim_speed(bfad, cmd, iocmd);
		break;
	case IOCMD_FCPIM_FAILOVER:
		rc = bfad_iocmd_cfg_fcpim(bfad, iocmd);
		break;
	case IOCMD_FCPIM_MODSTATS:
		rc = bfad_iocmd_fcpim_get_modstats(bfad, iocmd);
		break;
	case IOCMD_FCPIM_MODSTATSCLR:
		rc = bfad_iocmd_fcpim_clr_modstats(bfad, iocmd);
		break;
	case IOCMD_FCPIM_DEL_ITN_STATS:
		rc = bfad_iocmd_fcpim_get_del_itn_stats(bfad, iocmd);
		break;
	case IOCMD_ITNIM_GET_ATTR:
		rc = bfad_iocmd_itnim_get_attr(bfad, iocmd);
		break;
	case IOCMD_ITNIM_GET_IOSTATS:
		rc = bfad_iocmd_itnim_get_iostats(bfad, iocmd);
		break;
	case IOCMD_ITNIM_RESET_STATS:
		rc = bfad_iocmd_itnim_reset_stats(bfad, iocmd);
		break;
	case IOCMD_ITNIM_GET_ITNSTATS:
		rc = bfad_iocmd_itnim_get_itnstats(bfad, iocmd);
		break;
	case IOCMD_FCPORT_ENABLE:
		rc = bfad_iocmd_fcport_enable(bfad, iocmd);
		break;
	case IOCMD_FCPORT_DISABLE:
		rc = bfad_iocmd_fcport_disable(bfad, iocmd);
		break;
	case IOCMD_IOC_PCIFN_CFG:
		rc = bfad_iocmd_ioc_get_pcifn_cfg(bfad, iocmd);
		break;
	case IOCMD_PCIFN_CREATE:
		rc = bfad_iocmd_pcifn_create(bfad, iocmd);
		break;
	case IOCMD_PCIFN_DELETE:
		rc = bfad_iocmd_pcifn_delete(bfad, iocmd);
		break;
	case IOCMD_PCIFN_BW:
		rc = bfad_iocmd_pcifn_bw(bfad, iocmd);
		break;
	case IOCMD_ADAPTER_CFG_MODE:
		rc = bfad_iocmd_adapter_cfg_mode(bfad, iocmd);
		break;
	case IOCMD_PORT_CFG_MODE:
		rc = bfad_iocmd_port_cfg_mode(bfad, iocmd);
		break;
	case IOCMD_FLASH_ENABLE_OPTROM:
	case IOCMD_FLASH_DISABLE_OPTROM:
		rc = bfad_iocmd_ablk_optrom(bfad, cmd, iocmd);
		break;
	case IOCMD_FAA_QUERY:
		rc = bfad_iocmd_faa_query(bfad, iocmd);
		break;
	case IOCMD_CEE_GET_ATTR:
		rc = bfad_iocmd_cee_attr(bfad, iocmd, payload_len);
		break;
	case IOCMD_CEE_GET_STATS:
		rc = bfad_iocmd_cee_get_stats(bfad, iocmd, payload_len);
		break;
	case IOCMD_CEE_RESET_STATS:
		rc = bfad_iocmd_cee_reset_stats(bfad, iocmd);
		break;
	case IOCMD_SFP_MEDIA:
		rc = bfad_iocmd_sfp_media(bfad, iocmd);
		 break;
	case IOCMD_SFP_SPEED:
		rc = bfad_iocmd_sfp_speed(bfad, iocmd);
		break;
	case IOCMD_FLASH_GET_ATTR:
		rc = bfad_iocmd_flash_get_attr(bfad, iocmd);
		break;
	case IOCMD_FLASH_ERASE_PART:
		rc = bfad_iocmd_flash_erase_part(bfad, iocmd);
		break;
	case IOCMD_FLASH_UPDATE_PART:
		rc = bfad_iocmd_flash_update_part(bfad, iocmd, payload_len);
		break;
	case IOCMD_FLASH_READ_PART:
		rc = bfad_iocmd_flash_read_part(bfad, iocmd, payload_len);
		break;
	case IOCMD_DIAG_TEMP:
		rc = bfad_iocmd_diag_temp(bfad, iocmd);
		break;
	case IOCMD_DIAG_MEMTEST:
		rc = bfad_iocmd_diag_memtest(bfad, iocmd);
		break;
	case IOCMD_DIAG_LOOPBACK:
		rc = bfad_iocmd_diag_loopback(bfad, iocmd);
		break;
	case IOCMD_DIAG_FWPING:
		rc = bfad_iocmd_diag_fwping(bfad, iocmd);
		break;
	case IOCMD_DIAG_QUEUETEST:
		rc = bfad_iocmd_diag_queuetest(bfad, iocmd);
		break;
	case IOCMD_DIAG_SFP:
		rc = bfad_iocmd_diag_sfp(bfad, iocmd);
		break;
	case IOCMD_DIAG_LED:
		rc = bfad_iocmd_diag_led(bfad, iocmd);
		break;
	case IOCMD_DIAG_BEACON_LPORT:
		rc = bfad_iocmd_diag_beacon_lport(bfad, iocmd);
		break;
	case IOCMD_DIAG_LB_STAT:
		rc = bfad_iocmd_diag_lb_stat(bfad, iocmd);
		break;
	case IOCMD_DIAG_DPORT_ENABLE:
		rc = bfad_iocmd_diag_dport_enable(bfad, iocmd);
		break;
	case IOCMD_DIAG_DPORT_DISABLE:
		rc = bfad_iocmd_diag_dport_disable(bfad, iocmd);
		break;
	case IOCMD_DIAG_DPORT_SHOW:
		rc = bfad_iocmd_diag_dport_show(bfad, iocmd);
		break;
	case IOCMD_DIAG_DPORT_START:
		rc = bfad_iocmd_diag_dport_start(bfad, iocmd);
		break;
	case IOCMD_PHY_GET_ATTR:
		rc = bfad_iocmd_phy_get_attr(bfad, iocmd);
		break;
	case IOCMD_PHY_GET_STATS:
		rc = bfad_iocmd_phy_get_stats(bfad, iocmd);
		break;
	case IOCMD_PHY_UPDATE_FW:
		rc = bfad_iocmd_phy_update(bfad, iocmd, payload_len);
		break;
	case IOCMD_PHY_READ_FW:
		rc = bfad_iocmd_phy_read(bfad, iocmd, payload_len);
		break;
	case IOCMD_VHBA_QUERY:
		rc = bfad_iocmd_vhba_query(bfad, iocmd);
		break;
	case IOCMD_DEBUG_PORTLOG:
		rc = bfad_iocmd_porglog_get(bfad, iocmd);
		break;
	case IOCMD_DEBUG_FW_CORE:
		rc = bfad_iocmd_debug_fw_core(bfad, iocmd, payload_len);
		break;
	case IOCMD_DEBUG_FW_STATE_CLR:
	case IOCMD_DEBUG_PORTLOG_CLR:
	case IOCMD_DEBUG_START_DTRC:
	case IOCMD_DEBUG_STOP_DTRC:
		rc = bfad_iocmd_debug_ctl(bfad, iocmd, cmd);
		break;
	case IOCMD_DEBUG_PORTLOG_CTL:
		rc = bfad_iocmd_porglog_ctl(bfad, iocmd);
		break;
	case IOCMD_FCPIM_PROFILE_ON:
	case IOCMD_FCPIM_PROFILE_OFF:
		rc = bfad_iocmd_fcpim_cfg_profile(bfad, iocmd, cmd);
		break;
	case IOCMD_ITNIM_GET_IOPROFILE:
		rc = bfad_iocmd_itnim_get_ioprofile(bfad, iocmd);
		break;
	case IOCMD_FCPORT_GET_STATS:
		rc = bfad_iocmd_fcport_get_stats(bfad, iocmd);
		break;
	case IOCMD_FCPORT_RESET_STATS:
		rc = bfad_iocmd_fcport_reset_stats(bfad, iocmd);
		break;
	case IOCMD_BOOT_CFG:
		rc = bfad_iocmd_boot_cfg(bfad, iocmd);
		break;
	case IOCMD_BOOT_QUERY:
		rc = bfad_iocmd_boot_query(bfad, iocmd);
		break;
	case IOCMD_PREBOOT_QUERY:
		rc = bfad_iocmd_preboot_query(bfad, iocmd);
		break;
	case IOCMD_ETHBOOT_CFG:
		rc = bfad_iocmd_ethboot_cfg(bfad, iocmd);
		break;
	case IOCMD_ETHBOOT_QUERY:
		rc = bfad_iocmd_ethboot_query(bfad, iocmd);
		break;
	case IOCMD_TRUNK_ENABLE:
	case IOCMD_TRUNK_DISABLE:
		rc = bfad_iocmd_cfg_trunk(bfad, iocmd, cmd);
		break;
	case IOCMD_TRUNK_GET_ATTR:
		rc = bfad_iocmd_trunk_get_attr(bfad, iocmd);
		break;
	case IOCMD_QOS_ENABLE:
	case IOCMD_QOS_DISABLE:
		rc = bfad_iocmd_qos(bfad, iocmd, cmd);
		break;
	case IOCMD_QOS_GET_ATTR:
		rc = bfad_iocmd_qos_get_attr(bfad, iocmd);
		break;
	case IOCMD_QOS_GET_VC_ATTR:
		rc = bfad_iocmd_qos_get_vc_attr(bfad, iocmd);
		break;
	case IOCMD_QOS_GET_STATS:
		rc = bfad_iocmd_qos_get_stats(bfad, iocmd);
		break;
	case IOCMD_QOS_RESET_STATS:
		rc = bfad_iocmd_qos_reset_stats(bfad, iocmd);
		break;
	case IOCMD_QOS_SET_BW:
		rc = bfad_iocmd_qos_set_bw(bfad, iocmd);
		break;
	case IOCMD_VF_GET_STATS:
		rc = bfad_iocmd_vf_get_stats(bfad, iocmd);
		break;
	case IOCMD_VF_RESET_STATS:
		rc = bfad_iocmd_vf_clr_stats(bfad, iocmd);
		break;
	case IOCMD_FCPIM_THROTTLE_QUERY:
		rc = bfad_iocmd_fcpim_throttle_query(bfad, iocmd);
		break;
	case IOCMD_FCPIM_THROTTLE_SET:
		rc = bfad_iocmd_fcpim_throttle_set(bfad, iocmd);
		break;
	/* TFRU */
	case IOCMD_TFRU_READ:
		rc = bfad_iocmd_tfru_read(bfad, iocmd);
		break;
	case IOCMD_TFRU_WRITE:
		rc = bfad_iocmd_tfru_write(bfad, iocmd);
		break;
	/* FRU */
	case IOCMD_FRUVPD_READ:
		rc = bfad_iocmd_fruvpd_read(bfad, iocmd);
		break;
	case IOCMD_FRUVPD_UPDATE:
		rc = bfad_iocmd_fruvpd_update(bfad, iocmd);
		break;
	case IOCMD_FRUVPD_GET_MAX_SIZE:
		rc = bfad_iocmd_fruvpd_get_max_size(bfad, iocmd);
		break;
	default:
		rc = -EINVAL;
		break;
	}
	return rc;
}