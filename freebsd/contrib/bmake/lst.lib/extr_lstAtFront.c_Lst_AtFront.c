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
typedef  int /*<<< orphan*/  LstNode ;
typedef  int /*<<< orphan*/  Lst ;

/* Variables and functions */
 int /*<<< orphan*/  Lst_First (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_InsertBefore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

ReturnStatus
Lst_AtFront(Lst l, void *d)
{
    LstNode	front;

    front = Lst_First(l);
    return (Lst_InsertBefore(l, front, d));
}