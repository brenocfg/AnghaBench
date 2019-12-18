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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  g_strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gdk_keyval_name (int /*<<< orphan*/ ) ; 

void PERGTKKeyName(u32 key, char * name, int size)
{
   g_strlcpy(name, gdk_keyval_name(key), size);
}