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
typedef  int /*<<< orphan*/  DISC_INTERFACE ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_CACHE_PAGES ; 
 int /*<<< orphan*/  DEFAULT_SECTORS_PAGE ; 
 int fatMount (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool fatMountSimple (const char* name, const DISC_INTERFACE* interface)
{
   return fatMount (name, interface, 0, DEFAULT_CACHE_PAGES, DEFAULT_SECTORS_PAGE);
}