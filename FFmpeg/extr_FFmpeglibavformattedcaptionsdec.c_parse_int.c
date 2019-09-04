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
typedef  int int64_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ BETWEEN (int,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  next_byte (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  skip_spaces (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int parse_int(AVIOContext *pb, int *cur_byte, int64_t *result)
{
    int64_t val = 0;

    skip_spaces(pb, cur_byte);
    if ((unsigned)*cur_byte - '0' > 9)
        return AVERROR_INVALIDDATA;
    while (BETWEEN(*cur_byte, '0', '9')) {
        val = val * 10 + (*cur_byte - '0');
        next_byte(pb, cur_byte);
    }
    *result = val;
    return 0;
}