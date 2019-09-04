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
 int INT_MIN ; 
 int avio_rl16 (int /*<<< orphan*/ *) ; 
 int avio_rl32 (int /*<<< orphan*/ *) ; 
 int avio_rl64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_value(AVIOContext *pb, int type, int type2_size)
{
    switch (type) {
    case 2:
        return (type2_size == 32) ? avio_rl32(pb) : avio_rl16(pb);
    case 3:
        return avio_rl32(pb);
    case 4:
        return avio_rl64(pb);
    case 5:
        return avio_rl16(pb);
    default:
        return INT_MIN;
    }
}