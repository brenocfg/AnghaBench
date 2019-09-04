#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  scan_duration; int /*<<< orphan*/  valid_bitmask; int /*<<< orphan*/  scan_count; int /*<<< orphan*/  config_multicast_rate; int /*<<< orphan*/  config_frequency; int /*<<< orphan*/  dl_error_rate; int /*<<< orphan*/  dl_max_latency; int /*<<< orphan*/  dl_effective_latency; int /*<<< orphan*/  dl_min_latency; int /*<<< orphan*/  dl_max_bandwidth; int /*<<< orphan*/  dl_effective_bandwidth; int /*<<< orphan*/  ul_error_rate; int /*<<< orphan*/  ul_bytes_lost; int /*<<< orphan*/  ul_retxt_level; int /*<<< orphan*/  ul_max_latency; int /*<<< orphan*/  ul_effective_latency; int /*<<< orphan*/  ul_min_latency; int /*<<< orphan*/  ul_max_bandwidth; int /*<<< orphan*/  ul_effective_bandwidth; int /*<<< orphan*/  link_quality_metric; } ;
struct TYPE_18__ {int /*<<< orphan*/  mss_recommended; int /*<<< orphan*/  valid_bitmask; int /*<<< orphan*/  config_backoff_time; int /*<<< orphan*/  config_inactivity_time; int /*<<< orphan*/  dl_max_bandwidth; int /*<<< orphan*/  dl_effective_bandwidth; int /*<<< orphan*/  ul_max_queue_size; int /*<<< orphan*/  ul_avg_queue_size; int /*<<< orphan*/  ul_min_queue_size; int /*<<< orphan*/  ul_bytes_lost; int /*<<< orphan*/  ul_retxt_level; int /*<<< orphan*/  ul_max_latency; int /*<<< orphan*/  ul_effective_latency; int /*<<< orphan*/  ul_min_latency; int /*<<< orphan*/  ul_max_bandwidth; int /*<<< orphan*/  ul_effective_bandwidth; int /*<<< orphan*/  link_quality_metric; } ;
struct TYPE_12__ {TYPE_7__ wifi; TYPE_9__ cellular; } ;
struct TYPE_17__ {int /*<<< orphan*/  link_status_type; TYPE_3__ u; } ;
struct nstat_ifnet_descriptor {TYPE_8__ link_status; } ;
struct ifnet {scalar_t__ if_type; scalar_t__ if_subfamily; int /*<<< orphan*/  if_link_status_lock; struct if_link_status* if_link_status; } ;
struct if_wifi_status_v1 {int valid_bitmask; scalar_t__ ul_retxt_level; scalar_t__ config_frequency; int /*<<< orphan*/  scan_duration; int /*<<< orphan*/  scan_count; int /*<<< orphan*/  config_multicast_rate; int /*<<< orphan*/  dl_error_rate; int /*<<< orphan*/  dl_max_latency; int /*<<< orphan*/  dl_effective_latency; int /*<<< orphan*/  dl_min_latency; int /*<<< orphan*/  dl_max_bandwidth; int /*<<< orphan*/  dl_effective_bandwidth; int /*<<< orphan*/  ul_error_rate; int /*<<< orphan*/  ul_bytes_lost; int /*<<< orphan*/  ul_max_latency; int /*<<< orphan*/  ul_effective_latency; int /*<<< orphan*/  ul_min_latency; int /*<<< orphan*/  ul_max_bandwidth; int /*<<< orphan*/  ul_effective_bandwidth; int /*<<< orphan*/  link_quality_metric; } ;
struct TYPE_10__ {struct if_wifi_status_v1 if_status_v1; } ;
struct TYPE_11__ {TYPE_1__ if_wifi_u; } ;
struct if_cellular_status_v1 {int valid_bitmask; scalar_t__ ul_retxt_level; int /*<<< orphan*/  mss_recommended; int /*<<< orphan*/  config_backoff_time; int /*<<< orphan*/  config_inactivity_time; int /*<<< orphan*/  dl_max_bandwidth; int /*<<< orphan*/  dl_effective_bandwidth; int /*<<< orphan*/  ul_max_queue_size; int /*<<< orphan*/  ul_avg_queue_size; int /*<<< orphan*/  ul_min_queue_size; int /*<<< orphan*/  ul_bytes_lost; int /*<<< orphan*/  ul_max_latency; int /*<<< orphan*/  ul_effective_latency; int /*<<< orphan*/  ul_min_latency; int /*<<< orphan*/  ul_max_bandwidth; int /*<<< orphan*/  ul_effective_bandwidth; int /*<<< orphan*/  link_quality_metric; } ;
struct TYPE_13__ {struct if_cellular_status_v1 if_status_v1; } ;
struct TYPE_14__ {TYPE_4__ if_cell_u; } ;
struct TYPE_15__ {TYPE_2__ ifsr_wifi; TYPE_5__ ifsr_cell; } ;
struct if_link_status {scalar_t__ ifsr_version; TYPE_6__ ifsr_u; } ;
typedef  TYPE_7__ nstat_ifnet_desc_wifi_status ;
typedef  TYPE_8__ nstat_ifnet_desc_link_status ;
typedef  TYPE_9__ nstat_ifnet_desc_cellular_status ;

/* Variables and functions */
 scalar_t__ IFNET_SUBFAMILY_WIFI ; 
 scalar_t__ IFT_CELLULAR ; 
 scalar_t__ IF_CELLULAR_STATUS_REPORT_VERSION_1 ; 
 int IF_CELL_CONFIG_BACKOFF_TIME_VALID ; 
 int IF_CELL_CONFIG_INACTIVITY_TIME_VALID ; 
 int IF_CELL_DL_EFFECTIVE_BANDWIDTH_VALID ; 
 int IF_CELL_DL_MAX_BANDWIDTH_VALID ; 
 int IF_CELL_LINK_QUALITY_METRIC_VALID ; 
 int IF_CELL_UL_AVG_QUEUE_SIZE_VALID ; 
 int IF_CELL_UL_BYTES_LOST_VALID ; 
 int IF_CELL_UL_EFFECTIVE_BANDWIDTH_VALID ; 
 int IF_CELL_UL_EFFECTIVE_LATENCY_VALID ; 
 int IF_CELL_UL_MAX_BANDWIDTH_VALID ; 
 int IF_CELL_UL_MAX_LATENCY_VALID ; 
 int IF_CELL_UL_MAX_QUEUE_SIZE_VALID ; 
 int IF_CELL_UL_MIN_LATENCY_VALID ; 
 int IF_CELL_UL_MIN_QUEUE_SIZE_VALID ; 
 int IF_CELL_UL_MSS_RECOMMENDED_VALID ; 
 scalar_t__ IF_CELL_UL_RETXT_LEVEL_HIGH ; 
 scalar_t__ IF_CELL_UL_RETXT_LEVEL_LOW ; 
 scalar_t__ IF_CELL_UL_RETXT_LEVEL_MEDIUM ; 
 scalar_t__ IF_CELL_UL_RETXT_LEVEL_NONE ; 
 int IF_CELL_UL_RETXT_LEVEL_VALID ; 
 scalar_t__ IF_WIFI_CONFIG_FREQUENCY_2_4_GHZ ; 
 scalar_t__ IF_WIFI_CONFIG_FREQUENCY_5_0_GHZ ; 
 int IF_WIFI_CONFIG_FREQUENCY_VALID ; 
 int IF_WIFI_CONFIG_MULTICAST_RATE_VALID ; 
 int IF_WIFI_CONFIG_SCAN_COUNT_VALID ; 
 int IF_WIFI_CONFIG_SCAN_DURATION_VALID ; 
 int IF_WIFI_DL_EFFECTIVE_BANDWIDTH_VALID ; 
 int IF_WIFI_DL_EFFECTIVE_LATENCY_VALID ; 
 int IF_WIFI_DL_ERROR_RATE_VALID ; 
 int IF_WIFI_DL_MAX_BANDWIDTH_VALID ; 
 int IF_WIFI_DL_MAX_LATENCY_VALID ; 
 int IF_WIFI_DL_MIN_LATENCY_VALID ; 
 int IF_WIFI_LINK_QUALITY_METRIC_VALID ; 
 scalar_t__ IF_WIFI_STATUS_REPORT_VERSION_1 ; 
 int IF_WIFI_UL_BYTES_LOST_VALID ; 
 int IF_WIFI_UL_EFFECTIVE_BANDWIDTH_VALID ; 
 int IF_WIFI_UL_EFFECTIVE_LATENCY_VALID ; 
 int IF_WIFI_UL_ERROR_RATE_VALID ; 
 int IF_WIFI_UL_MAX_BANDWIDTH_VALID ; 
 int IF_WIFI_UL_MAX_LATENCY_VALID ; 
 int IF_WIFI_UL_MIN_LATENCY_VALID ; 
 scalar_t__ IF_WIFI_UL_RETXT_LEVEL_HIGH ; 
 scalar_t__ IF_WIFI_UL_RETXT_LEVEL_LOW ; 
 scalar_t__ IF_WIFI_UL_RETXT_LEVEL_MEDIUM ; 
 scalar_t__ IF_WIFI_UL_RETXT_LEVEL_NONE ; 
 int IF_WIFI_UL_RETXT_LEVEL_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_CELL_CONFIG_BACKOFF_TIME_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_CELL_CONFIG_INACTIVITY_TIME_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_CELL_DL_EFFECTIVE_BANDWIDTH_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_CELL_DL_MAX_BANDWIDTH_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_CELL_LINK_QUALITY_METRIC_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_CELL_MSS_RECOMMENDED_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_CELL_UL_AVG_QUEUE_SIZE_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_CELL_UL_BYTES_LOST_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_CELL_UL_EFFECTIVE_BANDWIDTH_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_CELL_UL_EFFECTIVE_LATENCY_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_CELL_UL_MAX_BANDWIDTH_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_CELL_UL_MAX_LATENCY_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_CELL_UL_MAX_QUEUE_SIZE_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_CELL_UL_MIN_LATENCY_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_CELL_UL_MIN_QUEUE_SIZE_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_CELL_UL_RETXT_LEVEL_HIGH ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_CELL_UL_RETXT_LEVEL_LOW ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_CELL_UL_RETXT_LEVEL_MEDIUM ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_CELL_UL_RETXT_LEVEL_NONE ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_CELL_UL_RETXT_LEVEL_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_LINK_STATUS_TYPE_CELLULAR ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_LINK_STATUS_TYPE_NONE ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_LINK_STATUS_TYPE_WIFI ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_CONFIG_FREQUENCY_2_4_GHZ ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_CONFIG_FREQUENCY_5_0_GHZ ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_CONFIG_FREQUENCY_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_CONFIG_MULTICAST_RATE_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_CONFIG_SCAN_COUNT_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_CONFIG_SCAN_DURATION_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_DL_EFFECTIVE_BANDWIDTH_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_DL_EFFECTIVE_LATENCY_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_DL_ERROR_RATE_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_DL_MAX_BANDWIDTH_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_DL_MAX_LATENCY_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_DL_MIN_LATENCY_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_LINK_QUALITY_METRIC_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_UL_BYTES_LOST_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_UL_EFFECTIVE_BANDWIDTH_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_UL_EFFECTIVE_LATENCY_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_UL_ERROR_RATE_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_UL_MAX_BANDWIDTH_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_UL_MAX_LATENCY_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_UL_MIN_LATENCY_VALID ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_UL_RETXT_LEVEL_HIGH ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_UL_RETXT_LEVEL_LOW ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_UL_RETXT_LEVEL_MEDIUM ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_UL_RETXT_LEVEL_NONE ; 
 int /*<<< orphan*/  NSTAT_IFNET_DESC_WIFI_UL_RETXT_LEVEL_VALID ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nstat_ifnet_copy_link_status(
	struct ifnet			*ifp,
	struct nstat_ifnet_descriptor	*desc)
{
	struct if_link_status *ifsr = ifp->if_link_status;
	nstat_ifnet_desc_link_status *link_status = &desc->link_status;

	link_status->link_status_type = NSTAT_IFNET_DESC_LINK_STATUS_TYPE_NONE;
	if (ifsr == NULL)
		return;

	lck_rw_lock_shared(&ifp->if_link_status_lock);

	if (ifp->if_type == IFT_CELLULAR) {

		nstat_ifnet_desc_cellular_status *cell_status = &link_status->u.cellular;
		struct if_cellular_status_v1 *if_cell_sr =
			&ifsr->ifsr_u.ifsr_cell.if_cell_u.if_status_v1;

		if (ifsr->ifsr_version != IF_CELLULAR_STATUS_REPORT_VERSION_1)
			goto done;

		link_status->link_status_type = NSTAT_IFNET_DESC_LINK_STATUS_TYPE_CELLULAR;

		if (if_cell_sr->valid_bitmask & IF_CELL_LINK_QUALITY_METRIC_VALID) {
			cell_status->valid_bitmask |= NSTAT_IFNET_DESC_CELL_LINK_QUALITY_METRIC_VALID;
			cell_status->link_quality_metric = if_cell_sr->link_quality_metric;
		}
		if (if_cell_sr->valid_bitmask & IF_CELL_UL_EFFECTIVE_BANDWIDTH_VALID) {
			cell_status->valid_bitmask |= NSTAT_IFNET_DESC_CELL_UL_EFFECTIVE_BANDWIDTH_VALID;
			cell_status->ul_effective_bandwidth = if_cell_sr->ul_effective_bandwidth;
		}
		if (if_cell_sr->valid_bitmask & IF_CELL_UL_MAX_BANDWIDTH_VALID) {
			cell_status->valid_bitmask |= NSTAT_IFNET_DESC_CELL_UL_MAX_BANDWIDTH_VALID;
			cell_status->ul_max_bandwidth = if_cell_sr->ul_max_bandwidth;
		}
		if (if_cell_sr->valid_bitmask & IF_CELL_UL_MIN_LATENCY_VALID) {
			cell_status->valid_bitmask |= NSTAT_IFNET_DESC_CELL_UL_MIN_LATENCY_VALID;
			cell_status->ul_min_latency = if_cell_sr->ul_min_latency;
		}
		if (if_cell_sr->valid_bitmask & IF_CELL_UL_EFFECTIVE_LATENCY_VALID) {
			cell_status->valid_bitmask |= NSTAT_IFNET_DESC_CELL_UL_EFFECTIVE_LATENCY_VALID;
			cell_status->ul_effective_latency = if_cell_sr->ul_effective_latency;
		}
		if (if_cell_sr->valid_bitmask & IF_CELL_UL_MAX_LATENCY_VALID) {
			cell_status->valid_bitmask |= NSTAT_IFNET_DESC_CELL_UL_MAX_LATENCY_VALID;
			cell_status->ul_max_latency = if_cell_sr->ul_max_latency;
		}
		if (if_cell_sr->valid_bitmask & IF_CELL_UL_RETXT_LEVEL_VALID) {
			cell_status->valid_bitmask |= NSTAT_IFNET_DESC_CELL_UL_RETXT_LEVEL_VALID;
			if (if_cell_sr->ul_retxt_level == IF_CELL_UL_RETXT_LEVEL_NONE)
				cell_status->ul_retxt_level = NSTAT_IFNET_DESC_CELL_UL_RETXT_LEVEL_NONE;
			else if (if_cell_sr->ul_retxt_level == IF_CELL_UL_RETXT_LEVEL_LOW)
				cell_status->ul_retxt_level = NSTAT_IFNET_DESC_CELL_UL_RETXT_LEVEL_LOW;
			else if (if_cell_sr->ul_retxt_level == IF_CELL_UL_RETXT_LEVEL_MEDIUM)
				cell_status->ul_retxt_level = NSTAT_IFNET_DESC_CELL_UL_RETXT_LEVEL_MEDIUM;
			else if (if_cell_sr->ul_retxt_level == IF_CELL_UL_RETXT_LEVEL_HIGH)
				cell_status->ul_retxt_level = NSTAT_IFNET_DESC_CELL_UL_RETXT_LEVEL_HIGH;
			else
				cell_status->valid_bitmask &= ~NSTAT_IFNET_DESC_CELL_UL_RETXT_LEVEL_VALID;
		}
		if (if_cell_sr->valid_bitmask & IF_CELL_UL_BYTES_LOST_VALID) {
			cell_status->valid_bitmask |= NSTAT_IFNET_DESC_CELL_UL_BYTES_LOST_VALID;
			cell_status->ul_bytes_lost = if_cell_sr->ul_bytes_lost;
		}
		if (if_cell_sr->valid_bitmask & IF_CELL_UL_MIN_QUEUE_SIZE_VALID) {
			cell_status->valid_bitmask |= NSTAT_IFNET_DESC_CELL_UL_MIN_QUEUE_SIZE_VALID;
			cell_status->ul_min_queue_size = if_cell_sr->ul_min_queue_size;
		}
		if (if_cell_sr->valid_bitmask & IF_CELL_UL_AVG_QUEUE_SIZE_VALID) {
			cell_status->valid_bitmask |= NSTAT_IFNET_DESC_CELL_UL_AVG_QUEUE_SIZE_VALID;
			cell_status->ul_avg_queue_size = if_cell_sr->ul_avg_queue_size;
		}
		if (if_cell_sr->valid_bitmask & IF_CELL_UL_MAX_QUEUE_SIZE_VALID) {
			cell_status->valid_bitmask |= NSTAT_IFNET_DESC_CELL_UL_MAX_QUEUE_SIZE_VALID;
			cell_status->ul_max_queue_size = if_cell_sr->ul_max_queue_size;
		}
		if (if_cell_sr->valid_bitmask & IF_CELL_DL_EFFECTIVE_BANDWIDTH_VALID) {
			cell_status->valid_bitmask |= NSTAT_IFNET_DESC_CELL_DL_EFFECTIVE_BANDWIDTH_VALID;
			cell_status->dl_effective_bandwidth = if_cell_sr->dl_effective_bandwidth;
		}
		if (if_cell_sr->valid_bitmask & IF_CELL_DL_MAX_BANDWIDTH_VALID) {
			cell_status->valid_bitmask |= NSTAT_IFNET_DESC_CELL_DL_MAX_BANDWIDTH_VALID;
			cell_status->dl_max_bandwidth = if_cell_sr->dl_max_bandwidth;
		}
		if (if_cell_sr->valid_bitmask & IF_CELL_CONFIG_INACTIVITY_TIME_VALID) {
			cell_status->valid_bitmask |= NSTAT_IFNET_DESC_CELL_CONFIG_INACTIVITY_TIME_VALID;
			cell_status->config_inactivity_time = if_cell_sr->config_inactivity_time;
		}
		if (if_cell_sr->valid_bitmask & IF_CELL_CONFIG_BACKOFF_TIME_VALID) {
			cell_status->valid_bitmask |= NSTAT_IFNET_DESC_CELL_CONFIG_BACKOFF_TIME_VALID;
			cell_status->config_backoff_time = if_cell_sr->config_backoff_time;
		}
		if (if_cell_sr->valid_bitmask & IF_CELL_UL_MSS_RECOMMENDED_VALID) {
			cell_status->valid_bitmask |= NSTAT_IFNET_DESC_CELL_MSS_RECOMMENDED_VALID;
			cell_status->mss_recommended = if_cell_sr->mss_recommended;
		}
	} else if (ifp->if_subfamily == IFNET_SUBFAMILY_WIFI) {

		nstat_ifnet_desc_wifi_status *wifi_status = &link_status->u.wifi;
		struct if_wifi_status_v1 *if_wifi_sr =
			&ifsr->ifsr_u.ifsr_wifi.if_wifi_u.if_status_v1;

		if (ifsr->ifsr_version != IF_WIFI_STATUS_REPORT_VERSION_1)
			goto done;

		link_status->link_status_type = NSTAT_IFNET_DESC_LINK_STATUS_TYPE_WIFI;

		if (if_wifi_sr->valid_bitmask & IF_WIFI_LINK_QUALITY_METRIC_VALID) {
			wifi_status->valid_bitmask |= NSTAT_IFNET_DESC_WIFI_LINK_QUALITY_METRIC_VALID;
			wifi_status->link_quality_metric = if_wifi_sr->link_quality_metric;
		}
		if (if_wifi_sr->valid_bitmask & IF_WIFI_UL_EFFECTIVE_BANDWIDTH_VALID) {
			wifi_status->valid_bitmask |= NSTAT_IFNET_DESC_WIFI_UL_EFFECTIVE_BANDWIDTH_VALID;
			wifi_status->ul_effective_bandwidth = if_wifi_sr->ul_effective_bandwidth;
		}
		if (if_wifi_sr->valid_bitmask & IF_WIFI_UL_MAX_BANDWIDTH_VALID) {
			wifi_status->valid_bitmask |= NSTAT_IFNET_DESC_WIFI_UL_MAX_BANDWIDTH_VALID;
			wifi_status->ul_max_bandwidth = if_wifi_sr->ul_max_bandwidth;
		}
		if (if_wifi_sr->valid_bitmask & IF_WIFI_UL_MIN_LATENCY_VALID) {
			wifi_status->valid_bitmask |= NSTAT_IFNET_DESC_WIFI_UL_MIN_LATENCY_VALID;
			wifi_status->ul_min_latency = if_wifi_sr->ul_min_latency;
		}
		if (if_wifi_sr->valid_bitmask & IF_WIFI_UL_EFFECTIVE_LATENCY_VALID) {
			wifi_status->valid_bitmask |= NSTAT_IFNET_DESC_WIFI_UL_EFFECTIVE_LATENCY_VALID;
			wifi_status->ul_effective_latency = if_wifi_sr->ul_effective_latency;
		}
		if (if_wifi_sr->valid_bitmask & IF_WIFI_UL_MAX_LATENCY_VALID) {
			wifi_status->valid_bitmask |= NSTAT_IFNET_DESC_WIFI_UL_MAX_LATENCY_VALID;
			wifi_status->ul_max_latency = if_wifi_sr->ul_max_latency;
		}
		if (if_wifi_sr->valid_bitmask & IF_WIFI_UL_RETXT_LEVEL_VALID) {
			wifi_status->valid_bitmask |= NSTAT_IFNET_DESC_WIFI_UL_RETXT_LEVEL_VALID;
			if (if_wifi_sr->ul_retxt_level == IF_WIFI_UL_RETXT_LEVEL_NONE)
				wifi_status->ul_retxt_level = NSTAT_IFNET_DESC_WIFI_UL_RETXT_LEVEL_NONE;
			else if (if_wifi_sr->ul_retxt_level == IF_WIFI_UL_RETXT_LEVEL_LOW)
				wifi_status->ul_retxt_level = NSTAT_IFNET_DESC_WIFI_UL_RETXT_LEVEL_LOW;
			else if (if_wifi_sr->ul_retxt_level == IF_WIFI_UL_RETXT_LEVEL_MEDIUM)
				wifi_status->ul_retxt_level = NSTAT_IFNET_DESC_WIFI_UL_RETXT_LEVEL_MEDIUM;
			else if (if_wifi_sr->ul_retxt_level == IF_WIFI_UL_RETXT_LEVEL_HIGH)
				wifi_status->ul_retxt_level = NSTAT_IFNET_DESC_WIFI_UL_RETXT_LEVEL_HIGH;
			else
				wifi_status->valid_bitmask &= ~NSTAT_IFNET_DESC_WIFI_UL_RETXT_LEVEL_VALID;
		}
		if (if_wifi_sr->valid_bitmask & IF_WIFI_UL_BYTES_LOST_VALID) {
			wifi_status->valid_bitmask |= NSTAT_IFNET_DESC_WIFI_UL_BYTES_LOST_VALID;
			wifi_status->ul_bytes_lost = if_wifi_sr->ul_bytes_lost;
		}
		if (if_wifi_sr->valid_bitmask & IF_WIFI_UL_ERROR_RATE_VALID) {
			wifi_status->valid_bitmask |= NSTAT_IFNET_DESC_WIFI_UL_ERROR_RATE_VALID;
			wifi_status->ul_error_rate = if_wifi_sr->ul_error_rate;
		}
		if (if_wifi_sr->valid_bitmask & IF_WIFI_DL_EFFECTIVE_BANDWIDTH_VALID) {
			wifi_status->valid_bitmask |= NSTAT_IFNET_DESC_WIFI_DL_EFFECTIVE_BANDWIDTH_VALID;
			wifi_status->dl_effective_bandwidth = if_wifi_sr->dl_effective_bandwidth;
		}
		if (if_wifi_sr->valid_bitmask & IF_WIFI_DL_MAX_BANDWIDTH_VALID) {
			wifi_status->valid_bitmask |= NSTAT_IFNET_DESC_WIFI_DL_MAX_BANDWIDTH_VALID;
			wifi_status->dl_max_bandwidth = if_wifi_sr->dl_max_bandwidth;
		}
		if (if_wifi_sr->valid_bitmask & IF_WIFI_DL_MIN_LATENCY_VALID) {
			wifi_status->valid_bitmask |= NSTAT_IFNET_DESC_WIFI_DL_MIN_LATENCY_VALID;
			wifi_status->dl_min_latency = if_wifi_sr->dl_min_latency;
		}
		if (if_wifi_sr->valid_bitmask & IF_WIFI_DL_EFFECTIVE_LATENCY_VALID) {
			wifi_status->valid_bitmask |= NSTAT_IFNET_DESC_WIFI_DL_EFFECTIVE_LATENCY_VALID;
			wifi_status->dl_effective_latency = if_wifi_sr->dl_effective_latency;
		}
		if (if_wifi_sr->valid_bitmask & IF_WIFI_DL_MAX_LATENCY_VALID) {
			wifi_status->valid_bitmask |= NSTAT_IFNET_DESC_WIFI_DL_MAX_LATENCY_VALID;
			wifi_status->dl_max_latency = if_wifi_sr->dl_max_latency;
		}
		if (if_wifi_sr->valid_bitmask & IF_WIFI_DL_ERROR_RATE_VALID) {
			wifi_status->valid_bitmask |= NSTAT_IFNET_DESC_WIFI_DL_ERROR_RATE_VALID;
			wifi_status->dl_error_rate = if_wifi_sr->dl_error_rate;
		}
		if (if_wifi_sr->valid_bitmask & IF_WIFI_CONFIG_FREQUENCY_VALID) {
			wifi_status->valid_bitmask |= NSTAT_IFNET_DESC_WIFI_CONFIG_FREQUENCY_VALID;
			if (if_wifi_sr->config_frequency == IF_WIFI_CONFIG_FREQUENCY_2_4_GHZ)
				wifi_status->config_frequency = NSTAT_IFNET_DESC_WIFI_CONFIG_FREQUENCY_2_4_GHZ;
			else if (if_wifi_sr->config_frequency == IF_WIFI_CONFIG_FREQUENCY_5_0_GHZ)
				wifi_status->config_frequency = NSTAT_IFNET_DESC_WIFI_CONFIG_FREQUENCY_5_0_GHZ;
			else
				wifi_status->valid_bitmask &= ~NSTAT_IFNET_DESC_WIFI_CONFIG_FREQUENCY_VALID;
		}
		if (if_wifi_sr->valid_bitmask & IF_WIFI_CONFIG_MULTICAST_RATE_VALID) {
			wifi_status->valid_bitmask |= NSTAT_IFNET_DESC_WIFI_CONFIG_MULTICAST_RATE_VALID;
			wifi_status->config_multicast_rate = if_wifi_sr->config_multicast_rate;
		}
		if (if_wifi_sr->valid_bitmask & IF_WIFI_CONFIG_SCAN_COUNT_VALID) {
			wifi_status->valid_bitmask |= NSTAT_IFNET_DESC_WIFI_CONFIG_SCAN_COUNT_VALID;
			wifi_status->scan_count = if_wifi_sr->scan_count;
		}
		if (if_wifi_sr->valid_bitmask & IF_WIFI_CONFIG_SCAN_DURATION_VALID) {
			wifi_status->valid_bitmask |= NSTAT_IFNET_DESC_WIFI_CONFIG_SCAN_DURATION_VALID;
			wifi_status->scan_duration = if_wifi_sr->scan_duration;
		}
	}

done:
	lck_rw_done(&ifp->if_link_status_lock);
}