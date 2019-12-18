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
typedef  int uint64_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int NEEDS_CHECKING ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int sign_extend (int,int) ; 

__attribute__((used)) static int ebml_read_sint(AVIOContext *pb, int size, int64_t *num)
{
    int n = 1;

    if (size == 0) {
        *num = 0;
    } else {
        *num = sign_extend(avio_r8(pb), 8);

        /* big-endian ordering; build up number */
        while (n++ < size)
            *num = ((uint64_t)*num << 8) | avio_r8(pb);
    }

    return NEEDS_CHECKING;
}