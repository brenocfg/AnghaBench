#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  reg_slc0_len; } ;
struct TYPE_8__ {TYPE_2__ pkt_len; } ;
struct TYPE_5__ {int val; } ;
struct TYPE_7__ {TYPE_1__ slc0_len_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_EARLY_LOGV (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int FIELD_TO_VALUE2 (int /*<<< orphan*/ ,int) ; 
 TYPE_4__ HOST ; 
 TYPE_3__ SLC ; 
 int /*<<< orphan*/  SLC_SLC0_LEN_WDATA ; 
 int /*<<< orphan*/  SLC_SLC0_LEN_WR ; 
 int /*<<< orphan*/  TAG ; 

__attribute__((used)) static inline void send_length_write(uint32_t len)
{
    SLC.slc0_len_conf.val = FIELD_TO_VALUE2(SLC_SLC0_LEN_WDATA, len) | FIELD_TO_VALUE2(SLC_SLC0_LEN_WR, 1);
    ESP_EARLY_LOGV(TAG, "send_length_write: %d, last_len: %08X", len, HOST.pkt_len.reg_slc0_len);
}