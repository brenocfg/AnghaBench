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

/* Variables and functions */
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  go (int /*<<< orphan*/ ,int,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static void
handle(int sig)
{
	go(0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
	exit(0);
}