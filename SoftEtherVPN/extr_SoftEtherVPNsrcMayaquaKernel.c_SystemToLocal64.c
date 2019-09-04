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
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;

/* Variables and functions */
 int /*<<< orphan*/  SystemToLocal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SystemToUINT64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UINT64ToSystem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

UINT64 SystemToLocal64(UINT64 t)
{
	SYSTEMTIME st;
	UINT64ToSystem(&st, t);
	SystemToLocal(&st, &st);
	return SystemToUINT64(&st);
}