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
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  ecryptfs_printk (int /*<<< orphan*/ ,char*) ; 

int ecryptfs_parse_packet_length(unsigned char *data, size_t *size,
				 size_t *length_size)
{
	int rc = 0;

	(*length_size) = 0;
	(*size) = 0;
	if (data[0] < 192) {
		/* One-byte length */
		(*size) = (unsigned char)data[0];
		(*length_size) = 1;
	} else if (data[0] < 224) {
		/* Two-byte length */
		(*size) = (((unsigned char)(data[0]) - 192) * 256);
		(*size) += ((unsigned char)(data[1]) + 192);
		(*length_size) = 2;
	} else if (data[0] == 255) {
		/* Five-byte length; we're not supposed to see this */
		ecryptfs_printk(KERN_ERR, "Five-byte packet length not "
				"supported\n");
		rc = -EINVAL;
		goto out;
	} else {
		ecryptfs_printk(KERN_ERR, "Error parsing packet length\n");
		rc = -EINVAL;
		goto out;
	}
out:
	return rc;
}