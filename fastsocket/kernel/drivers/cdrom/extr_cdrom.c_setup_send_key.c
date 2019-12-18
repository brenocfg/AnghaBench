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
struct packet_command {unsigned int* cmd; int buflen; int /*<<< orphan*/  data_direction; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGC_DATA_WRITE ; 
 unsigned int GPCMD_SEND_KEY ; 

__attribute__((used)) static void setup_send_key(struct packet_command *cgc, unsigned agid, unsigned type)
{
	cgc->cmd[0] = GPCMD_SEND_KEY;
	cgc->cmd[10] = type | (agid << 6);
	switch (type) {
		case 1: {
			cgc->buflen = 16;
			break;
		}
		case 3: {
			cgc->buflen = 12;
			break;
		}
		case 6: {
			cgc->buflen = 8;
			break;
		}
	}
	cgc->cmd[9] = cgc->buflen;
	cgc->data_direction = CGC_DATA_WRITE;
}