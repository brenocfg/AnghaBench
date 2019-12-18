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
typedef  int /*<<< orphan*/  Lst ;
typedef  int Boolean ;

/* Variables and functions */
 scalar_t__ LstIsEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LstValid (int /*<<< orphan*/ ) ; 

Boolean
Lst_IsEmpty(Lst l)
{
    return ( ! LstValid (l) || LstIsEmpty(l));
}