#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct of_device {TYPE_1__* node; } ;
typedef  int ssize_t ;
struct TYPE_2__ {char* name; char* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* of_get_property (TYPE_1__*,char*,int*) ; 
 int snprintf (char*,int,char*,char*,char*) ; 

ssize_t of_device_get_modalias(struct of_device *ofdev,
				char *str, ssize_t len)
{
	const char *compat;
	int cplen, i;
	ssize_t tsize, csize, repend;

	/* Name & Type */
	csize = snprintf(str, len, "of:N%sT%s",
				ofdev->node->name, ofdev->node->type);

	/* Get compatible property if any */
	compat = of_get_property(ofdev->node, "compatible", &cplen);
	if (!compat)
		return csize;

	/* Find true end (we tolerate multiple \0 at the end */
	for (i = (cplen - 1); i >= 0 && !compat[i]; i--)
		cplen--;
	if (!cplen)
		return csize;
	cplen++;

	/* Check space (need cplen+1 chars including final \0) */
	tsize = csize + cplen;
	repend = tsize;

	if (csize >= len)		/* @ the limit, all is already filled */
		return tsize;

	if (tsize >= len) {		/* limit compat list */
		cplen = len - csize - 1;
		repend = len;
	}

	/* Copy and do char replacement */
	memcpy(&str[csize + 1], compat, cplen);
	for (i = csize; i < repend; i++) {
		char c = str[i];
		if (c == '\0')
			str[i] = 'C';
		else if (c == ' ')
			str[i] = '_';
	}

	return tsize;
}