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
 int /*<<< orphan*/  BiosRom ; 
 int T123Load (int /*<<< orphan*/ ,int,int,char const*) ; 

int LoadBios(const char *filename)
{
   return T123Load(BiosRom, 0x80000, 2, filename);
}