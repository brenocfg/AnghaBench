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
typedef  int /*<<< orphan*/  ReturnStatus ;
typedef  int /*<<< orphan*/  Lst ;

/* Variables and functions */
 int /*<<< orphan*/  FAILURE ; 
 scalar_t__ FALSE ; 
 scalar_t__ LstValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_InsertAfter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  Lst_Last (int /*<<< orphan*/ ) ; 

ReturnStatus
Lst_EnQueue(Lst l, void *d)
{
    if (LstValid (l) == FALSE) {
	return (FAILURE);
    }

    return (Lst_InsertAfter(l, Lst_Last(l), d));
}