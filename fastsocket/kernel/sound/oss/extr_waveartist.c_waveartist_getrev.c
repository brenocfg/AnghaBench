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
typedef  int /*<<< orphan*/  wavnc_info ;

/* Variables and functions */
 unsigned int WACMD_GETREV ; 
 int /*<<< orphan*/  waveartist_cmd (int /*<<< orphan*/ *,int,unsigned int*,int,unsigned int*) ; 

__attribute__((used)) static int
waveartist_getrev(wavnc_info *devc, char *rev)
{
	unsigned int temp[2];
	unsigned int cmd = WACMD_GETREV;

	waveartist_cmd(devc, 1, &cmd, 2, temp);

	rev[0] = temp[0] >> 8;
	rev[1] = temp[0] & 255;
	rev[2] = '\0';

	return temp[0];
}