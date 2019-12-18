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
typedef  size_t u32 ;
struct TYPE_2__ {int cmd; int /*<<< orphan*/  cb; int /*<<< orphan*/  offset; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DVD_LowSeek (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __Read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* __dvd_cmdlist ; 
 size_t __dvd_nextcmdnum ; 

__attribute__((used)) static u32 __ProcessNextCmd()
{
	u32 cmd_num = __dvd_nextcmdnum;
	if(__dvd_cmdlist[cmd_num].cmd==0x0001) {
		__dvd_nextcmdnum++;
		__Read(__dvd_cmdlist[cmd_num].buf,__dvd_cmdlist[cmd_num].len,__dvd_cmdlist[cmd_num].offset,__dvd_cmdlist[cmd_num].cb);
		return 1;
	}

	if(__dvd_cmdlist[cmd_num].cmd==0x0002) {
		__dvd_nextcmdnum++;
		DVD_LowSeek(__dvd_cmdlist[cmd_num].offset,__dvd_cmdlist[cmd_num].cb);
		return 1;
	}
	return 0;
}