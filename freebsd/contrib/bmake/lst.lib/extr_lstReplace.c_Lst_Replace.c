#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* datum; } ;
typedef  int /*<<< orphan*/  ReturnStatus ;
typedef  TYPE_1__* LstNode ;

/* Variables and functions */
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  SUCCESS ; 

ReturnStatus
Lst_Replace(LstNode ln, void *d)
{
    if (ln == NULL) {
	return (FAILURE);
    } else {
	(ln)->datum = d;
	return (SUCCESS);
    }
}