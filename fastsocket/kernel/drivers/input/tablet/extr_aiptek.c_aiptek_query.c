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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  programmableDelay; } ;
struct aiptek {TYPE_1__ curSetting; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ aiptek_command (struct aiptek*,unsigned char,unsigned char) ; 
 int aiptek_get_report (struct aiptek*,int,int,int*,int const) ; 
 int /*<<< orphan*/  dbg (char*,int,int,int) ; 
 int get_unaligned_le16 (int*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aiptek_query(struct aiptek *aiptek, unsigned char command, unsigned char data)
{
	const int sizeof_buf = 3 * sizeof(u8);
	int ret;
	u8 *buf;

	buf = kmalloc(sizeof_buf, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	buf[0] = 2;
	buf[1] = command;
	buf[2] = data;

	if (aiptek_command(aiptek, command, data) != 0) {
		kfree(buf);
		return -EIO;
	}
	msleep(aiptek->curSetting.programmableDelay);

	if ((ret =
	     aiptek_get_report(aiptek, 3, 2, buf, sizeof_buf)) != sizeof_buf) {
		dbg("aiptek_query failed: returned 0x%02x 0x%02x 0x%02x",
		    buf[0], buf[1], buf[2]);
		ret = -EIO;
	} else {
		ret = get_unaligned_le16(buf + 1);
	}
	kfree(buf);
	return ret;
}