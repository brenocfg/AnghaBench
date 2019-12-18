#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* buffer; int index; } ;
typedef  TYPE_1__ SStream ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 
 scalar_t__ strlen (char const*) ; 

void SStream_concat0(SStream *ss, const char *s)
{
#ifndef CAPSTONE_DIET
	unsigned int len = (unsigned int) strlen(s);

	memcpy(ss->buffer + ss->index, s, len);
	ss->index += len;
	ss->buffer[ss->index] = '\0';
#endif
}