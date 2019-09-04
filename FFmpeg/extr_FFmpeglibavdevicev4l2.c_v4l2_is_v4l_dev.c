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
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static int v4l2_is_v4l_dev(const char *name)
{
    return !strncmp(name, "video", 5) ||
           !strncmp(name, "radio", 5) ||
           !strncmp(name, "vbi", 3) ||
           !strncmp(name, "v4l-subdev", 10);
}