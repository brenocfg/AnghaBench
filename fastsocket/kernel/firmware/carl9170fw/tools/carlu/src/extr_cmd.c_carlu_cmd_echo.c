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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ const uint32_t ;
struct carlu {int dummy; } ;
typedef  int /*<<< orphan*/  message ;
typedef  int /*<<< orphan*/  _message ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170_CMD_ECHO ; 
 int EIO ; 
 int carlusb_cmd (struct carlu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

int carlu_cmd_echo(struct carlu *ar, const uint32_t message)
{
	uint32_t _message;
	int ret;

	ret = carlusb_cmd(ar, CARL9170_CMD_ECHO,
			     (uint8_t *)&message, sizeof(message),
			     (uint8_t *)&_message, sizeof(_message));

	if (ret == 0)
		ret = (message == _message) ? 0 : -EIO;

	return ret;
}