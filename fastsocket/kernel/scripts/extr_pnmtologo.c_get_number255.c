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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned int get_number (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int get_number255(FILE *fp, unsigned int maxval)
{
    unsigned int val = get_number(fp);
    return (255*val+maxval/2)/maxval;
}