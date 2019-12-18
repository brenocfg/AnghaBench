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
typedef  int /*<<< orphan*/  apr_uint32_t ;
typedef  int /*<<< orphan*/  apr_byte_t ;

/* Variables and functions */
 scalar_t__ isLittleEndian () ; 

__attribute__((used)) static void maybe_byte_reverse(apr_uint32_t *buffer, int count)
{
    int i;
    apr_byte_t ct[4], *cp;

    if (isLittleEndian()) {	/* do the swap only if it is little endian */
	count /= sizeof(apr_uint32_t);
	cp = (apr_byte_t *) buffer;
	for (i = 0; i < count; ++i) {
	    ct[0] = cp[0];
	    ct[1] = cp[1];
	    ct[2] = cp[2];
	    ct[3] = cp[3];
	    cp[0] = ct[3];
	    cp[1] = ct[2];
	    cp[2] = ct[1];
	    cp[3] = ct[0];
	    cp += sizeof(apr_uint32_t);
	}
    }
}