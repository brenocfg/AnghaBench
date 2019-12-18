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
typedef  int /*<<< orphan*/  uch ;

/* Variables and functions */
 int /*<<< orphan*/  png_sig_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int readpng2_check_sig(uch *sig, int num)
{
    return !png_sig_cmp(sig, 0, num);
}