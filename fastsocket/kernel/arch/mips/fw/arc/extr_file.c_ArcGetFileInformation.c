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
struct linux_finfo {int dummy; } ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  LONG ;

/* Variables and functions */
 int /*<<< orphan*/  ARC_CALL2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct linux_finfo*) ; 
 int /*<<< orphan*/  get_finfo ; 

LONG
ArcGetFileInformation(ULONG FileID, struct linux_finfo *Information)
{
	return ARC_CALL2(get_finfo, FileID, Information);
}