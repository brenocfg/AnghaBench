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
struct mon_reader_bin {unsigned int b_size; TYPE_1__* b_vec; } ;
struct TYPE_2__ {unsigned char* ptr; } ;

/* Variables and functions */
 int CHUNK_SIZE ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,unsigned int) ; 

__attribute__((used)) static void mon_copy_to_buff(const struct mon_reader_bin *this,
    unsigned int off, const unsigned char *from, unsigned int length)
{
	unsigned int step_len;
	unsigned char *buf;
	unsigned int in_page;

	while (length) {
		/*
		 * Determine step_len.
		 */
		step_len = length;
		in_page = CHUNK_SIZE - (off & (CHUNK_SIZE-1));
		if (in_page < step_len)
			step_len = in_page;

		/*
		 * Copy data and advance pointers.
		 */
		buf = this->b_vec[off / CHUNK_SIZE].ptr + off % CHUNK_SIZE;
		memcpy(buf, from, step_len);
		if ((off += step_len) >= this->b_size) off = 0;
		from += step_len;
		length -= step_len;
	}
}