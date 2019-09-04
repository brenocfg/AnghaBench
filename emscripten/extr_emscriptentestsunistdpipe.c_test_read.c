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
 unsigned char* buf ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int read (int,unsigned char*,int) ; 

void test_read(int fd0, unsigned char *ch, int size)
{
    memset(buf, 0, sizeof buf);
    assert(read(fd0, buf, size) == size);
    for(int i = 0; i < sizeof buf; ++i)
    {
        unsigned char correct_ch = (i < size) ? (*ch)++ : 0;
        assert(buf[i] == correct_ch);
    }
}