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
 int /*<<< orphan*/  compute_edit_offset (char*,int,int,int*,int /*<<< orphan*/ ) ; 

int
dlg_edit_offset(char *string, int chr_offset, int x_last)
{
    int result;

    compute_edit_offset(string, chr_offset, x_last, &result, 0);

    return result;
}