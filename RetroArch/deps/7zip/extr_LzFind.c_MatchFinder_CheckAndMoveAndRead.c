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
typedef  int /*<<< orphan*/  CMatchFinder ;

/* Variables and functions */
 int /*<<< orphan*/  MatchFinder_MoveBlock (int /*<<< orphan*/ *) ; 
 scalar_t__ MatchFinder_NeedMove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MatchFinder_ReadBlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void MatchFinder_CheckAndMoveAndRead(CMatchFinder *p)
{
  if (MatchFinder_NeedMove(p))
    MatchFinder_MoveBlock(p);
  MatchFinder_ReadBlock(p);
}