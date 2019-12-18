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
struct Scsi_Host {TYPE_1__* hostt; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int (* proc_info ) (struct Scsi_Host*,char*,char**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct Scsi_Host*,char*,char**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_scsi_read(char *buffer, char **start, off_t offset,
			  int length, int *eof, void *data)
{
	struct Scsi_Host *shost = data;
	int n;

	n = shost->hostt->proc_info(shost, buffer, start, offset, length, 0);
	*eof = (n < length);

	return n;
}