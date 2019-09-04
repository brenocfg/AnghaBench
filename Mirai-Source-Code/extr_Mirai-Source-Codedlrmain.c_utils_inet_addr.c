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
 unsigned int HTONL (unsigned long) ; 

unsigned int utils_inet_addr(unsigned char one, unsigned char two, unsigned char three, unsigned char four)
{
    unsigned long ip = 0;

    ip |= (one << 24);
    ip |= (two << 16);
    ip |= (three << 8);
    ip |= (four << 0);
    return HTONL(ip);
}