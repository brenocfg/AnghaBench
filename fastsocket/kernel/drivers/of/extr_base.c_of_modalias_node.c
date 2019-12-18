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
struct device_node {int dummy; } ;
struct TYPE_3__ {char* of_device; char const* modalias; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  of_device_is_compatible (struct device_node*,char const*) ; 
 char* of_get_property (struct device_node*,char*,int*) ; 
 TYPE_1__* of_modalias_table ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

int of_modalias_node(struct device_node *node, char *modalias, int len)
{
	int i, cplen;
	const char *compatible;
	const char *p;

	/* 1. search for exception list entry */
	for (i = 0; i < ARRAY_SIZE(of_modalias_table); i++) {
		compatible = of_modalias_table[i].of_device;
		if (!of_device_is_compatible(node, compatible))
			continue;
		strlcpy(modalias, of_modalias_table[i].modalias, len);
		return 0;
	}

	compatible = of_get_property(node, "compatible", &cplen);
	if (!compatible)
		return -ENODEV;

	/* 2. take first compatible entry and strip manufacturer */
	p = strchr(compatible, ',');
	if (!p)
		return -ENODEV;
	p++;
	strlcpy(modalias, p, len);
	return 0;
}