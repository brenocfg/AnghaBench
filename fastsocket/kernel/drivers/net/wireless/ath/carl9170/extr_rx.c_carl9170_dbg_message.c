#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int err_counter; int /*<<< orphan*/  bug_counter; } ;
struct ar9170 {TYPE_1__* hw; TYPE_2__ fw; } ;
typedef  enum carl9170_restart_reasons { ____Placeholder_carl9170_restart_reasons } carl9170_restart_reasons ;
struct TYPE_3__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170_BUG_MAGIC ; 
 int /*<<< orphan*/  CARL9170_ERR_MAGIC ; 
 int CARL9170_RR_FATAL_FIRMWARE_ERROR ; 
 int CARL9170_RR_NO_REASON ; 
 int CARL9170_RR_TOO_MANY_FIRMWARE_ERRORS ; 
 int /*<<< orphan*/  carl9170_restart (struct ar9170*,int) ; 
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wiphy_info (int /*<<< orphan*/ ,char*,int,char const*) ; 

__attribute__((used)) static void carl9170_dbg_message(struct ar9170 *ar, const char *buf, u32 len)
{
	bool restart = false;
	enum carl9170_restart_reasons reason = CARL9170_RR_NO_REASON;

	if (len > 3) {
		if (memcmp(buf, CARL9170_ERR_MAGIC, 3) == 0) {
			ar->fw.err_counter++;
			if (ar->fw.err_counter > 3) {
				restart = true;
				reason = CARL9170_RR_TOO_MANY_FIRMWARE_ERRORS;
			}
		}

		if (memcmp(buf, CARL9170_BUG_MAGIC, 3) == 0) {
			ar->fw.bug_counter++;
			restart = true;
			reason = CARL9170_RR_FATAL_FIRMWARE_ERROR;
		}
	}

	wiphy_info(ar->hw->wiphy, "FW: %.*s\n", len, buf);

	if (restart)
		carl9170_restart(ar, reason);
}