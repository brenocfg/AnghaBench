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
 int /*<<< orphan*/  DVD_RESETSOFT ; 
 int /*<<< orphan*/  DVD_Reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dvd_stateerrorcb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dvd_storeerror (int) ; 

void __dvd_statetimeout()
{
	__dvd_storeerror(0x01234568);
	DVD_Reset(DVD_RESETSOFT);
	__dvd_stateerrorcb(0);
}