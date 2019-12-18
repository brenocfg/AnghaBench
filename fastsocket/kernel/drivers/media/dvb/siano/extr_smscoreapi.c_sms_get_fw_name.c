#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smscore_device_t {int dummy; } ;
typedef  enum sms_device_type_st { ____Placeholder_sms_device_type_st } sms_device_type_st ;
struct TYPE_2__ {char** fw; } ;

/* Variables and functions */
 TYPE_1__* sms_get_board (int /*<<< orphan*/ ) ; 
 char*** smscore_fw_lkup ; 
 int /*<<< orphan*/  smscore_get_board_id (struct smscore_device_t*) ; 

__attribute__((used)) static inline char *sms_get_fw_name(struct smscore_device_t *coredev,
				    int mode, enum sms_device_type_st type)
{
	char **fw = sms_get_board(smscore_get_board_id(coredev))->fw;
	return (fw && fw[mode]) ? fw[mode] : smscore_fw_lkup[mode][type];
}