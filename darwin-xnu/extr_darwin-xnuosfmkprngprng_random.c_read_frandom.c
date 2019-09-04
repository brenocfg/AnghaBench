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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ u_int ;

/* Variables and functions */
 int MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  read_erandom (int /*<<< orphan*/ *,int) ; 

void
read_frandom(void * buffer, u_int numBytes)
{
	uint8_t * buffer_bytes = buffer;
	int nbytes;

	/*
	 * Split up into requests for blocks smaller than
	 * than the DBRG request limit. iThis limit is private but
	 * for NISTHMAC it's known to be greater then 4096.
	 */
	while (numBytes) {
		nbytes = MIN(numBytes, PAGE_SIZE);
		read_erandom(buffer_bytes, nbytes);
		buffer_bytes += nbytes;
		numBytes -= nbytes;
	}
}