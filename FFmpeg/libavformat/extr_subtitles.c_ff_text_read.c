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
typedef  int /*<<< orphan*/  FFTextReader ;

/* Variables and functions */
 int /*<<< orphan*/  ff_text_r8 (int /*<<< orphan*/ *) ; 

void ff_text_read(FFTextReader *r, char *buf, size_t size)
{
    for ( ; size > 0; size--)
        *buf++ = ff_text_r8(r);
}