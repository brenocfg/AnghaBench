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
struct v4l2_audio {int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct v4l2_audio*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int radio_g_audio(struct file *file, void *priv,
					struct v4l2_audio *a)
{
	memset(a, 0, sizeof(*a));
	strcpy(a->name, "Radio");
	return 0;
}