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
struct carlu {int dummy; } ;
struct carl9170_cmd_head {int dummy; } ;
struct TYPE_2__ {int cmd; unsigned int len; } ;
struct carl9170_cmd {TYPE_1__ hdr; } ;
typedef  enum carl9170_cmd_oids { ____Placeholder_carl9170_cmd_oids } carl9170_cmd_oids ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct carl9170_cmd* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct carl9170_cmd* malloc (int) ; 

struct carl9170_cmd *carlu_cmd_buf(struct carlu *ar,
	const enum carl9170_cmd_oids cmd, const unsigned int len)
{
	struct carl9170_cmd *tmp;

	if (len % 4 || (sizeof(struct carl9170_cmd_head) + len > 64))
		return ERR_PTR(-EINVAL);

	tmp = malloc(sizeof(struct carl9170_cmd_head) + len);
	if (tmp) {
		tmp->hdr.cmd = cmd;
		tmp->hdr.len = len;
	}
	return tmp;
}