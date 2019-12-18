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
 scalar_t__ ISCNTRL (int) ; 
 scalar_t__ ISGRAPH (int) ; 
 scalar_t__ ISSPACE (int) ; 

__attribute__((used)) static bool urlchar_needs_escaping(int c)
{
    return !(ISCNTRL(c) || ISSPACE(c) || ISGRAPH(c));
}