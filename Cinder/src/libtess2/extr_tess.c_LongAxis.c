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
typedef  int /*<<< orphan*/  TESSreal ;

/* Variables and functions */
 scalar_t__ ABS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int LongAxis( TESSreal v[3] )
{
	int i = 0;

	if( ABS(v[1]) > ABS(v[0]) ) { i = 1; }
	if( ABS(v[2]) > ABS(v[i]) ) { i = 2; }
	return i;
}