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
struct scsi_device {int /*<<< orphan*/  host; } ;
struct block_device {int dummy; } ;
typedef  int sector_t ;
struct TYPE_2__ {int translation; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 TYPE_1__* HOSTDATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int aha1740_biosparam(struct scsi_device *sdev,
			     struct block_device *dev,
			     sector_t capacity, int* ip)
{
	int size = capacity;
	int extended = HOSTDATA(sdev->host)->translation;

	DEB(printk("aha1740_biosparam\n"));
	if (extended && (ip[2] > 1024))	{
		ip[0] = 255;
		ip[1] = 63;
		ip[2] = size / (255 * 63);
	} else {
		ip[0] = 64;
		ip[1] = 32;
		ip[2] = size >> 11;
	}
	return 0;
}