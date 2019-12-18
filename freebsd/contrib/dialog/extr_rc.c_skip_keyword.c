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
 int /*<<< orphan*/  UCH (char) ; 
 scalar_t__ isalnum (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
skip_keyword(char *str, int n)
{
    while (isalnum(UCH(str[n])) && str[n] != '\0')
	n++;
    return n;
}