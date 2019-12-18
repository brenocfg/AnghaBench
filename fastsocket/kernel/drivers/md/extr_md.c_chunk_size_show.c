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
struct mddev {scalar_t__ reshape_position; int chunk_sectors; int new_chunk_sectors; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ MaxSector ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 

__attribute__((used)) static ssize_t
chunk_size_show(struct mddev *mddev, char *page)
{
	if (mddev->reshape_position != MaxSector &&
	    mddev->chunk_sectors != mddev->new_chunk_sectors)
		return sprintf(page, "%d (%d)\n",
			       mddev->new_chunk_sectors << 9,
			       mddev->chunk_sectors << 9);
	return sprintf(page, "%d\n", mddev->chunk_sectors << 9);
}