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
 int /*<<< orphan*/  nextoct () ; 
 int readc () ; 

__attribute__((used)) static int read_octal_char(int c) {
    int r = c - '0';
    if (!nextoct())
        return r;
    r = (r << 3) | (readc() - '0');
    if (!nextoct())
        return r;
    return (r << 3) | (readc() - '0');
}