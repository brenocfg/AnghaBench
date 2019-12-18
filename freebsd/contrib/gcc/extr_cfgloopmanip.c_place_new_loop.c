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
struct loops {int num; struct loop** parray; } ;
struct loop {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 struct loop** xrealloc (struct loop**,int) ; 

__attribute__((used)) static void
place_new_loop (struct loops *loops, struct loop *loop)
{
  loops->parray =
    xrealloc (loops->parray, (loops->num + 1) * sizeof (struct loop *));
  loops->parray[loops->num] = loop;

  loop->num = loops->num++;
}