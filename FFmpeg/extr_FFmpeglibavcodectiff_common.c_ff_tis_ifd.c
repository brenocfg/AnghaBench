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
 int FF_ARRAY_ELEMS (unsigned int*) ; 
 unsigned int* ifd_tags ; 

int ff_tis_ifd(unsigned tag)
{
    int i;
    for (i = 0; i < FF_ARRAY_ELEMS(ifd_tags); i++) {
        if (ifd_tags[i] == tag) {
            return i + 1;
        }
    }
    return 0;
}