#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t pcnt_unit_t ;
typedef  scalar_t__ pcnt_evt_type_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_6__ {TYPE_2__* conf_unit; } ;
struct TYPE_4__ {scalar_t__ thr_zero_en; scalar_t__ thr_thres1_en; scalar_t__ thr_thres0_en; scalar_t__ thr_h_lim_en; scalar_t__ thr_l_lim_en; } ;
struct TYPE_5__ {TYPE_1__ conf0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_3__ PCNT ; 
 int /*<<< orphan*/  PCNT_CHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PCNT_EVT_H_LIM ; 
 scalar_t__ PCNT_EVT_L_LIM ; 
 scalar_t__ PCNT_EVT_MAX ; 
 scalar_t__ PCNT_EVT_THRES_0 ; 
 scalar_t__ PCNT_EVT_THRES_1 ; 
 int /*<<< orphan*/  PCNT_EVT_TYPE_ERR_STR ; 
 scalar_t__ PCNT_EVT_ZERO ; 
 int /*<<< orphan*/  PCNT_UNIT_ERR_STR ; 
 size_t PCNT_UNIT_MAX ; 

esp_err_t pcnt_event_disable(pcnt_unit_t unit, pcnt_evt_type_t evt_type)
{
    PCNT_CHECK(unit < PCNT_UNIT_MAX, PCNT_UNIT_ERR_STR, ESP_ERR_INVALID_ARG);
    PCNT_CHECK(evt_type < PCNT_EVT_MAX, PCNT_EVT_TYPE_ERR_STR, ESP_ERR_INVALID_ARG);
    if(evt_type == PCNT_EVT_L_LIM) {
        PCNT.conf_unit[unit].conf0.thr_l_lim_en = 0;
    } else if(evt_type == PCNT_EVT_H_LIM) {
        PCNT.conf_unit[unit].conf0.thr_h_lim_en = 0;
    } else if(evt_type == PCNT_EVT_THRES_0) {
        PCNT.conf_unit[unit].conf0.thr_thres0_en = 0;
    } else if(evt_type == PCNT_EVT_THRES_1) {
        PCNT.conf_unit[unit].conf0.thr_thres1_en = 0;
    } else if(evt_type == PCNT_EVT_ZERO) {
        PCNT.conf_unit[unit].conf0.thr_zero_en = 0;
    }
    return ESP_OK;
}