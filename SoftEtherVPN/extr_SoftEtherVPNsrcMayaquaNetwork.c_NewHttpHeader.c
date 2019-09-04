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
typedef  int /*<<< orphan*/  HTTP_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/ * NewHttpHeaderEx (char*,char*,char*,int) ; 

HTTP_HEADER *NewHttpHeader(char *method, char *target, char *version)
{
	return NewHttpHeaderEx(method, target, version, false);
}