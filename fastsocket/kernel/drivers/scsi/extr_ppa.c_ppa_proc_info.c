#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {int dummy; } ;
struct TYPE_8__ {size_t mode; char* recon_tmo; TYPE_2__* dev; } ;
typedef  TYPE_3__ ppa_struct ;
typedef  int off_t ;
struct TYPE_7__ {TYPE_1__* port; } ;
struct TYPE_6__ {char* name; } ;

/* Variables and functions */
 char** PPA_MODE_STRING ; 
 char* PPA_VERSION ; 
 TYPE_3__* ppa_dev (struct Scsi_Host*) ; 
 int ppa_proc_write (TYPE_3__*,char*,int) ; 
 scalar_t__ sprintf (char*,char*,char*) ; 

__attribute__((used)) static int ppa_proc_info(struct Scsi_Host *host, char *buffer, char **start, off_t offset, int length, int inout)
{
	int len = 0;
	ppa_struct *dev = ppa_dev(host);

	if (inout)
		return ppa_proc_write(dev, buffer, length);

	len += sprintf(buffer + len, "Version : %s\n", PPA_VERSION);
	len +=
	    sprintf(buffer + len, "Parport : %s\n",
		    dev->dev->port->name);
	len +=
	    sprintf(buffer + len, "Mode    : %s\n",
		    PPA_MODE_STRING[dev->mode]);
#if PPA_DEBUG > 0
	len +=
	    sprintf(buffer + len, "recon_tmo : %lu\n", dev->recon_tmo);
#endif

	/* Request for beyond end of buffer */
	if (offset > length)
		return 0;

	*start = buffer + offset;
	len -= offset;
	if (len > length)
		len = length;
	return len;
}