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
typedef  int /*<<< orphan*/  MatroskaDemuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int EBML_UNKNOWN_LENGTH ; 
 int ebml_read_num (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int*,int) ; 

__attribute__((used)) static int ebml_read_length(MatroskaDemuxContext *matroska, AVIOContext *pb,
                            uint64_t *number)
{
    int res = ebml_read_num(matroska, pb, 8, number, 1);
    if (res > 0 && *number + 1 == 1ULL << (7 * res))
        *number = EBML_UNKNOWN_LENGTH;
    return res;
}