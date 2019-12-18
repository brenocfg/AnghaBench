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
typedef  int uint8_t ;
struct carlu {int dummy; } ;
struct TYPE_2__ {scalar_t__ len; } ;
struct carl9170_rsp {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  carlu_handle_command (struct carlu*,struct carl9170_rsp*,scalar_t__) ; 
 int /*<<< orphan*/  carlu_handle_data (struct carlu*,int*,unsigned int) ; 

__attribute__((used)) static void __carlu_rx(struct carlu *ar, uint8_t *buf, unsigned int len)
{
	unsigned int i;

	i = 0;

	/* weird thing, but this is the same in the original driver */
	while (len > 2 && i < 12 && buf[0] == 0xff && buf[1] == 0xff) {
		i += 2;
		len -= 2;
		buf += 2;
	}

	if (i == 12) {
		struct carl9170_rsp *cmd;
		i = 0;

		while (i < len) {
			cmd = (void *) &buf[i];

			carlu_handle_command(ar, cmd, cmd->hdr.len + 4);
			i += cmd->hdr.len + 4;
		}
	} else {
		carlu_handle_data(ar, buf, len);
	}
}