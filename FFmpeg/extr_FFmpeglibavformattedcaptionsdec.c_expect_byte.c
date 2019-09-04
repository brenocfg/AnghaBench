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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int ERR_CODE (int) ; 
 int /*<<< orphan*/  next_byte (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  skip_spaces (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int expect_byte(AVIOContext *pb, int *cur_byte, uint8_t c)
{
    skip_spaces(pb, cur_byte);
    if (*cur_byte != c)
        return ERR_CODE(*cur_byte);
    next_byte(pb, cur_byte);
    return 0;
}