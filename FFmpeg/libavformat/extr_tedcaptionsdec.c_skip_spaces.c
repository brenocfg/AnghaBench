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
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  next_byte (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void skip_spaces(AVIOContext *pb, int *cur_byte)
{
    while (*cur_byte == ' '  || *cur_byte == '\t' ||
           *cur_byte == '\n' || *cur_byte == '\r')
        next_byte(pb, cur_byte);
}