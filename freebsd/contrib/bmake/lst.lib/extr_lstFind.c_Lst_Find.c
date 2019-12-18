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
typedef  int /*<<< orphan*/  LstNode ;
typedef  int /*<<< orphan*/  Lst ;

/* Variables and functions */
 int /*<<< orphan*/  Lst_FindFrom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int (*) (void const*,void const*)) ; 
 int /*<<< orphan*/  Lst_First (int /*<<< orphan*/ ) ; 

LstNode
Lst_Find(Lst l, const void *d, int (*cProc)(const void *, const void *))
{
    return (Lst_FindFrom(l, Lst_First(l), d, cProc));
}