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
typedef  unsigned int uint32_t ;
typedef  int /*<<< orphan*/  DTEntry ;

/* Variables and functions */
 scalar_t__ DTGetProperty (int /*<<< orphan*/ ,char*,void**,unsigned int*) ; 
 scalar_t__ DTLookupEntry (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ kSuccess ; 

uint32_t
PE_get_random_seed(unsigned char *dst_random_seed, uint32_t request_size)
{
	DTEntry		entryP;
	uint32_t	size = 0;
	void		*dt_random_seed;

        if ((DTLookupEntry(NULL, "/chosen", &entryP) == kSuccess)
	    && (DTGetProperty(entryP, "random-seed",
				(void **)&dt_random_seed, &size) == kSuccess)) {
		unsigned char *src_random_seed;
		unsigned int i;
		unsigned int null_count = 0;

		src_random_seed = (unsigned char *)dt_random_seed;

		if (size > request_size) size = request_size;

		/*
		 * Copy from the device tree into the destination buffer,
		 * count the number of null bytes and null out the device tree.
		 */
		for (i=0 ; i< size; i++, src_random_seed++, dst_random_seed++) {
			*dst_random_seed = *src_random_seed;
			null_count += *src_random_seed == (unsigned char)0;
			*src_random_seed = (unsigned char)0;
		}
		if (null_count == size)
			/* All nulls is no seed - return 0 */
			size = 0;
	}

	return(size);
}