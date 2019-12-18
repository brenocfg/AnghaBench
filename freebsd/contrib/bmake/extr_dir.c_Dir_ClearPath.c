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
typedef  int /*<<< orphan*/  Path ;
typedef  int /*<<< orphan*/  Lst ;

/* Variables and functions */
 int /*<<< orphan*/  Dir_Destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ Lst_DeQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_IsEmpty (int /*<<< orphan*/ ) ; 

void
Dir_ClearPath(Lst path)
{
    Path    *p;
    while (!Lst_IsEmpty(path)) {
	p = (Path *)Lst_DeQueue(path);
	Dir_Destroy(p);
    }
}