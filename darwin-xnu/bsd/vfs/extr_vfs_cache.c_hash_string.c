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

/* Variables and functions */
 unsigned int* crc32tab ; 

unsigned int
hash_string(const char *cp, int len)
{
    unsigned hash = 0;

    if (len) {
            while (len--) {
		    hash = crc32tab[((hash >> 24) ^ (unsigned char)*cp++)] ^ hash << 8;
	    }
    } else {
            while (*cp != '\0') {
		    hash = crc32tab[((hash >> 24) ^ (unsigned char)*cp++)] ^ hash << 8;
	    }
    }
    /*
     * the crc generator can legitimately generate
     * a 0... however, 0 for us means that we
     * haven't computed a hash, so use 1 instead
     */
    if (hash == 0)
            hash = 1;
    return hash;
}