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
typedef  int /*<<< orphan*/  u8 ;
struct carl9170_disable_key_cmd {int /*<<< orphan*/  user; } ;
struct ar9170 {int dummy; } ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170_CMD_DKEY ; 
 int carl9170_exec_cmd (struct ar9170*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/  const) ; 

int carl9170_disable_key(struct ar9170 *ar, const u8 id)
{
	struct carl9170_disable_key_cmd key = { };

	key.user = cpu_to_le16(id);

	return carl9170_exec_cmd(ar, CARL9170_CMD_DKEY,
		sizeof(key), (u8 *)&key, 0, NULL);
}