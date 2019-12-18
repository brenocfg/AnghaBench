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
struct edd_device {int /*<<< orphan*/  mbr_signature; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  left ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
edd_show_mbr_signature(struct edd_device *edev, char *buf)
{
	char *p = buf;
	p += scnprintf(p, left, "0x%08x\n", edev->mbr_signature);
	return (p - buf);
}