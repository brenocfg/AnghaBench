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
struct rsxx_cardinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_TO_DEV (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ ,char*,int,char const*) ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*,int,char const*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,char const*) ; 
 int /*<<< orphan*/  dev_emerg (int /*<<< orphan*/ ,char*,int,char const*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,char const*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,char const*) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*,int,char const*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,char const*) ; 

__attribute__((used)) static void hw_log_msg(struct rsxx_cardinfo *card, const char *str, int len)
{
	static char level;

	/*
	 * New messages start with "<#>", where # is the log level. Messages
	 * that extend past the log buffer will use the previous level
	 */
	if ((len > 3) && (str[0] == '<') && (str[2] == '>')) {
		level = str[1];
		str += 3; /* Skip past the log level. */
		len -= 3;
	}

	switch (level) {
	case '0':
		dev_emerg(CARD_TO_DEV(card), "HW: %.*s", len, str);
		break;
	case '1':
		dev_alert(CARD_TO_DEV(card), "HW: %.*s", len, str);
		break;
	case '2':
		dev_crit(CARD_TO_DEV(card), "HW: %.*s", len, str);
		break;
	case '3':
		dev_err(CARD_TO_DEV(card), "HW: %.*s", len, str);
		break;
	case '4':
		dev_warn(CARD_TO_DEV(card), "HW: %.*s", len, str);
		break;
	case '5':
		dev_notice(CARD_TO_DEV(card), "HW: %.*s", len, str);
		break;
	case '6':
		dev_info(CARD_TO_DEV(card), "HW: %.*s", len, str);
		break;
	case '7':
		dev_dbg(CARD_TO_DEV(card), "HW: %.*s", len, str);
		break;
	default:
		dev_info(CARD_TO_DEV(card), "HW: %.*s", len, str);
		break;
	}
}