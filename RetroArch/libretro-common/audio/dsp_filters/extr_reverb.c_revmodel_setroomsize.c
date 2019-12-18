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
struct revmodel {scalar_t__ roomsize; } ;

/* Variables and functions */
 scalar_t__ offsetroom ; 
 int /*<<< orphan*/  revmodel_update (struct revmodel*) ; 
 float scaleroom ; 

__attribute__((used)) static void revmodel_setroomsize(struct revmodel *rev, float value)
{
   rev->roomsize = value * scaleroom + offsetroom;
   revmodel_update(rev);
}