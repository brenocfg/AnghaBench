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
 char* COM_ParseExt (char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtrue ; 

char *COM_Parse( char **data_p )
{
	return COM_ParseExt( data_p, qtrue );
}