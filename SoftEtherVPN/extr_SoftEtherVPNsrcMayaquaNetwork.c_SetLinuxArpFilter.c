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
typedef  int /*<<< orphan*/  IO ;

/* Variables and functions */
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FileCreate (char*) ; 
 int /*<<< orphan*/  FileFlush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FileWrite (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrLen (char*) ; 

void SetLinuxArpFilter()
{
	char *filename = "/proc/sys/net/ipv4/conf/all/arp_filter";
	char *data = "1\n";
	IO *o;

	o = FileCreate(filename);
	if (o == NULL)
	{
		return;
	}

	FileWrite(o, data, StrLen(data));
	FileFlush(o);

	FileClose(o);
}