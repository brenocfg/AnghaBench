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
 int waveartist_cmd (int /*<<< orphan*/ *,int,unsigned int*,int,unsigned int*) ; 

__attribute__((used)) static inline int
waveartist_cmd2(wavnc_info *devc, unsigned int cmd, unsigned int arg)
{
	unsigned int vals[2];

	vals[0] = cmd;
	vals[1] = arg;

	return waveartist_cmd(devc, 2, vals, 1, vals);
}