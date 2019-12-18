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
typedef  scalar_t__ UWORD ;

/* Variables and functions */
 scalar_t__ Devices_GetAtariPath (size_t,int /*<<< orphan*/ ) ; 
 size_t Devices_GetNumber (int) ; 
 int /*<<< orphan*/ * Devices_atari_h_dir ; 
 int /*<<< orphan*/  Util_catpath (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atari_filename ; 
 int /*<<< orphan*/  atari_path ; 
 size_t h_devnum ; 
 int /*<<< orphan*/  host_path ; 

__attribute__((used)) static UWORD Devices_GetHostPath(int set_textmode)
{
	UWORD bufadr;
	h_devnum = Devices_GetNumber(set_textmode);
	if (h_devnum < 0)
		return 0;
	bufadr = Devices_GetAtariPath(h_devnum, atari_filename);
	if (bufadr == 0)
		return 0;
	Util_catpath(host_path, Devices_atari_h_dir[h_devnum], atari_path);
	return bufadr;
}