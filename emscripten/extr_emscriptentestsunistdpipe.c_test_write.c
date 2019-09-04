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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * buf ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int write (int,int /*<<< orphan*/ *,int) ; 

void test_write(int fd1, unsigned char *ch, int size)
{
    memset(buf, 0, sizeof buf);
    for(int i = 0; i < size; ++i)
        buf[i] = (*ch)++;
    assert(write(fd1, buf, size) == size);
}