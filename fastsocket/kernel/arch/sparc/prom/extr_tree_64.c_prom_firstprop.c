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
 int /*<<< orphan*/  P1275_ARG_OUT_32B ; 
 int P1275_INOUT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p1275_cmd (char*,int,int,char*,char*) ; 

inline char *prom_firstprop(int node, char *buffer)
{
	*buffer = 0;
	if(node == -1) return buffer;
	p1275_cmd ("nextprop", P1275_ARG(2,P1275_ARG_OUT_32B)|
			       P1275_INOUT(3, 0), 
			       node, (char *) 0x0, buffer);
	return buffer;
}