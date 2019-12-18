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
struct ipv6_devconf {int /*<<< orphan*/  accept_dad; int /*<<< orphan*/  disable_ipv6; int /*<<< orphan*/  mc_forwarding; int /*<<< orphan*/  optimistic_dad; int /*<<< orphan*/  accept_source_route; int /*<<< orphan*/  proxy_ndp; int /*<<< orphan*/  accept_ra_rt_info_max_plen; int /*<<< orphan*/  rtr_probe_interval; int /*<<< orphan*/  accept_ra_rtr_pref; int /*<<< orphan*/  accept_ra_pinfo; int /*<<< orphan*/  accept_ra_defrtr; int /*<<< orphan*/  max_addresses; int /*<<< orphan*/  max_desync_factor; int /*<<< orphan*/  regen_max_retry; int /*<<< orphan*/  temp_prefered_lft; int /*<<< orphan*/  temp_valid_lft; int /*<<< orphan*/  use_tempaddr; int /*<<< orphan*/  force_mld_version; int /*<<< orphan*/  rtr_solicit_delay; int /*<<< orphan*/  rtr_solicit_interval; int /*<<< orphan*/  rtr_solicits; int /*<<< orphan*/  dad_transmits; int /*<<< orphan*/  autoconf; int /*<<< orphan*/  accept_redirects; int /*<<< orphan*/  accept_ra; int /*<<< orphan*/  mtu6; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  forwarding; } ;
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t DEVCONF_ACCEPT_DAD ; 
 size_t DEVCONF_ACCEPT_RA ; 
 size_t DEVCONF_ACCEPT_RA_DEFRTR ; 
 size_t DEVCONF_ACCEPT_RA_PINFO ; 
 size_t DEVCONF_ACCEPT_RA_RTR_PREF ; 
 size_t DEVCONF_ACCEPT_RA_RT_INFO_MAX_PLEN ; 
 size_t DEVCONF_ACCEPT_REDIRECTS ; 
 size_t DEVCONF_ACCEPT_SOURCE_ROUTE ; 
 size_t DEVCONF_AUTOCONF ; 
 size_t DEVCONF_DAD_TRANSMITS ; 
 size_t DEVCONF_DISABLE_IPV6 ; 
 size_t DEVCONF_FORCE_MLD_VERSION ; 
 size_t DEVCONF_FORWARDING ; 
 size_t DEVCONF_HOPLIMIT ; 
 int DEVCONF_MAX ; 
 size_t DEVCONF_MAX_ADDRESSES ; 
 size_t DEVCONF_MAX_DESYNC_FACTOR ; 
 size_t DEVCONF_MC_FORWARDING ; 
 size_t DEVCONF_MTU6 ; 
 size_t DEVCONF_OPTIMISTIC_DAD ; 
 size_t DEVCONF_PROXY_NDP ; 
 size_t DEVCONF_REGEN_MAX_RETRY ; 
 size_t DEVCONF_RTR_PROBE_INTERVAL ; 
 size_t DEVCONF_RTR_SOLICITS ; 
 size_t DEVCONF_RTR_SOLICIT_DELAY ; 
 size_t DEVCONF_RTR_SOLICIT_INTERVAL ; 
 size_t DEVCONF_TEMP_PREFERED_LFT ; 
 size_t DEVCONF_TEMP_VALID_LFT ; 
 size_t DEVCONF_USE_TEMPADDR ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void ipv6_store_devconf(struct ipv6_devconf *cnf,
				__s32 *array, int bytes)
{
	BUG_ON(bytes < (DEVCONF_MAX * 4));

	memset(array, 0, bytes);
	array[DEVCONF_FORWARDING] = cnf->forwarding;
	array[DEVCONF_HOPLIMIT] = cnf->hop_limit;
	array[DEVCONF_MTU6] = cnf->mtu6;
	array[DEVCONF_ACCEPT_RA] = cnf->accept_ra;
	array[DEVCONF_ACCEPT_REDIRECTS] = cnf->accept_redirects;
	array[DEVCONF_AUTOCONF] = cnf->autoconf;
	array[DEVCONF_DAD_TRANSMITS] = cnf->dad_transmits;
	array[DEVCONF_RTR_SOLICITS] = cnf->rtr_solicits;
	array[DEVCONF_RTR_SOLICIT_INTERVAL] = cnf->rtr_solicit_interval;
	array[DEVCONF_RTR_SOLICIT_DELAY] = cnf->rtr_solicit_delay;
	array[DEVCONF_FORCE_MLD_VERSION] = cnf->force_mld_version;
#ifdef CONFIG_IPV6_PRIVACY
	array[DEVCONF_USE_TEMPADDR] = cnf->use_tempaddr;
	array[DEVCONF_TEMP_VALID_LFT] = cnf->temp_valid_lft;
	array[DEVCONF_TEMP_PREFERED_LFT] = cnf->temp_prefered_lft;
	array[DEVCONF_REGEN_MAX_RETRY] = cnf->regen_max_retry;
	array[DEVCONF_MAX_DESYNC_FACTOR] = cnf->max_desync_factor;
#endif
	array[DEVCONF_MAX_ADDRESSES] = cnf->max_addresses;
	array[DEVCONF_ACCEPT_RA_DEFRTR] = cnf->accept_ra_defrtr;
	array[DEVCONF_ACCEPT_RA_PINFO] = cnf->accept_ra_pinfo;
#ifdef CONFIG_IPV6_ROUTER_PREF
	array[DEVCONF_ACCEPT_RA_RTR_PREF] = cnf->accept_ra_rtr_pref;
	array[DEVCONF_RTR_PROBE_INTERVAL] = cnf->rtr_probe_interval;
#ifdef CONFIG_IPV6_ROUTE_INFO
	array[DEVCONF_ACCEPT_RA_RT_INFO_MAX_PLEN] = cnf->accept_ra_rt_info_max_plen;
#endif
#endif
	array[DEVCONF_PROXY_NDP] = cnf->proxy_ndp;
	array[DEVCONF_ACCEPT_SOURCE_ROUTE] = cnf->accept_source_route;
#ifdef CONFIG_IPV6_OPTIMISTIC_DAD
	array[DEVCONF_OPTIMISTIC_DAD] = cnf->optimistic_dad;
#endif
#ifdef CONFIG_IPV6_MROUTE
	array[DEVCONF_MC_FORWARDING] = cnf->mc_forwarding;
#endif
	array[DEVCONF_DISABLE_IPV6] = cnf->disable_ipv6;
	array[DEVCONF_ACCEPT_DAD] = cnf->accept_dad;
}