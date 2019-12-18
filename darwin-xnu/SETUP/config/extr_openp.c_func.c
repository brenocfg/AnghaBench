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
 int /*<<< orphan*/  flgs ; 
 int /*<<< orphan*/  mod ; 
 scalar_t__ open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ value ; 

__attribute__((used)) static int
func(char *fnam)
{
	value = open (fnam,flgs,mod);
	return (value < 0);
}