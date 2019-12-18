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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  h1940bt_enable (int) ; 
 int /*<<< orphan*/  isspace (char) ; 
 int simple_strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t h1940bt_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	int new_state;
	char *endp;

	new_state = simple_strtoul(buf, &endp, 0);
	if (*endp && !isspace(*endp))
		return -EINVAL;

	h1940bt_enable(new_state);

	return count;
}