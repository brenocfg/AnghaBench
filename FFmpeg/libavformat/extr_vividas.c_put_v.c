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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */

__attribute__((used)) static void put_v(uint8_t *p, unsigned v)
{
    if (v>>28)
        *p++ = ((v>>28)&0x7f)|0x80;
    if (v>>21)
        *p++ = ((v>>21)&0x7f)|0x80;
    if (v>>14)
        *p++ = ((v>>14)&0x7f)|0x80;
    if (v>>7)
        *p++ =  ((v>>7)&0x7f)|0x80;
}