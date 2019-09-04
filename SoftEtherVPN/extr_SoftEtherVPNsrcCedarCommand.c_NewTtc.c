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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  TT_PRINT_PROC ;
typedef  int /*<<< orphan*/  TTC ;

/* Variables and functions */
 int /*<<< orphan*/ * NewTtcEx (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

TTC *NewTtc(char *host, UINT port, UINT numtcp, UINT type, UINT64 span, bool dbl, bool raw, TT_PRINT_PROC *print_proc, void *param)
{
	return NewTtcEx(host, port, numtcp, type, span, dbl, raw, print_proc, param, NULL, NULL);
}