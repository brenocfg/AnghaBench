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
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  COMPARE ;

/* Variables and functions */
 int /*<<< orphan*/ * NewListEx2 (int /*<<< orphan*/ *,int,int) ; 

LIST *NewListEx(COMPARE *cmp, bool fast)
{
	return NewListEx2(cmp, fast, false);
}