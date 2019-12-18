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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  csum ; 
 int /*<<< orphan*/  exit (int) ; 
 size_t fwrite (void const*,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outfd ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  xcsum ; 

__attribute__((used)) static void write_out(const void *data, size_t size)
{
	const uint8_t *p = data;
	size_t loop;

	for (loop = 0; loop < size; loop++) {
		csum += p[loop];
		xcsum += p[loop];
	}

	if (fwrite(data, 1, size, outfd) != size) {
		perror("write");
		exit(1);
	}
}