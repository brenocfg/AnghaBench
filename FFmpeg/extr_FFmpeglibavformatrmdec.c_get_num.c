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
 int avio_rb16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_num(AVIOContext *pb, int *len)
{
    int n, n1;

    n = avio_rb16(pb);
    (*len)-=2;
    n &= 0x7FFF;
    if (n >= 0x4000) {
        return n - 0x4000;
    } else {
        n1 = avio_rb16(pb);
        (*len)-=2;
        return (n << 16) | n1;
    }
}