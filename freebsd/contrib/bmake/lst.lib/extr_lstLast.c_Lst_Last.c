#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * lastPtr; } ;
typedef  int /*<<< orphan*/ * LstNode ;
typedef  TYPE_1__* Lst ;

/* Variables and functions */
 scalar_t__ LstIsEmpty (TYPE_1__*) ; 
 int /*<<< orphan*/  LstValid (TYPE_1__*) ; 

LstNode
Lst_Last(Lst l)
{
    if (!LstValid(l) || LstIsEmpty (l)) {
	return NULL;
    } else {
	return (l->lastPtr);
    }
}