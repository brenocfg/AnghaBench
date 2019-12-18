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
struct pt_unit {int last_sense; } ;

/* Variables and functions */
 char ATAPI_TEST_READY ; 
 int /*<<< orphan*/  DBMSG (char*) ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  pt_atapi (struct pt_unit*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_sleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pt_ready_wait(struct pt_unit *tape, int tmo)
{
	char tr_cmd[12] = { ATAPI_TEST_READY, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int k, p;

	k = 0;
	while (k < tmo) {
		tape->last_sense = 0;
		pt_atapi(tape, tr_cmd, 0, NULL, DBMSG("test unit ready"));
		p = tape->last_sense;
		if (!p)
			return 0;
		if (!(((p & 0xffff) == 0x0402) || ((p & 0xff) == 6)))
			return p;
		k++;
		pt_sleep(HZ);
	}
	return 0x000020;	/* timeout */
}