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
struct isci_orom {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  blob_name ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 size_t fwrite (struct isci_orom*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 

int write_blob(struct isci_orom *isci_orom)
{
	FILE *fd;
	int err;
	size_t count;

	fd = fopen(blob_name, "w+");
	if (!fd) {
		perror("Open file for write failed");
		fclose(fd);
		return -EIO;
	}

	count = fwrite(isci_orom, sizeof(struct isci_orom), 1, fd);
	if (count != 1) {
		perror("Write data failed");
		fclose(fd);
		return -EIO;
	}

	fclose(fd);

	return 0;
}