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
 int P1275_ARG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P1275_ARG_OUT_BUF ; 
 int P1275_INOUT (int,int) ; 
 int /*<<< orphan*/  P1275_SIZE (int) ; 
 int p1275_cmd (char*,int,int,char*,int /*<<< orphan*/ ) ; 

int prom_ihandle2path(int handle, char *buffer, int bufsize)
{
	return p1275_cmd("instance-to-path",
			 P1275_ARG(1,P1275_ARG_OUT_BUF)|
			 P1275_INOUT(3, 1),
			 handle, buffer, P1275_SIZE(bufsize));
}