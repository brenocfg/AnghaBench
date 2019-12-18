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
 int EditString (int,int,char const*,char*,int,int,int,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int BasicUIEditString(const char *title, char *string, int size)
{
	return EditString(0x9a, 0x94, title, string, size, 3, 11, 32, NULL, -1);
}