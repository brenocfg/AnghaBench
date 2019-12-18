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
struct adfs_discrecord {int log2secsize; int idlen; scalar_t__* unused52; int /*<<< orphan*/  disc_size_high; } ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adfs_checkdiscrecord(struct adfs_discrecord *dr)
{
	int i;

	/* sector size must be 256, 512 or 1024 bytes */
	if (dr->log2secsize != 8 &&
	    dr->log2secsize != 9 &&
	    dr->log2secsize != 10)
		return 1;

	/* idlen must be at least log2secsize + 3 */
	if (dr->idlen < dr->log2secsize + 3)
		return 1;

	/* we cannot have such a large disc that we
	 * are unable to represent sector offsets in
	 * 32 bits.  This works out at 2.0 TB.
	 */
	if (le32_to_cpu(dr->disc_size_high) >> dr->log2secsize)
		return 1;

	/* idlen must be no greater than 19 v2 [1.0] */
	if (dr->idlen > 19)
		return 1;

	/* reserved bytes should be zero */
	for (i = 0; i < sizeof(dr->unused52); i++)
		if (dr->unused52[i] != 0)
			return 1;

	return 0;
}