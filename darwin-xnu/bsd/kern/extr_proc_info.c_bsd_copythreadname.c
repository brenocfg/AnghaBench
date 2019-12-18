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
struct uthread {char* pth_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAXTHREADNAMESIZE ; 
 int /*<<< orphan*/  bcopy (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ kalloc (int /*<<< orphan*/ ) ; 

void
bsd_copythreadname(void *dst_uth, void *src_uth)
{
	struct uthread *dst_ut = (struct uthread *)dst_uth;
	struct uthread *src_ut = (struct uthread *)src_uth;

	if (src_ut->pth_name == NULL)
		return;

	if (dst_ut->pth_name == NULL) {
		dst_ut->pth_name = (char *)kalloc(MAXTHREADNAMESIZE);
		if (dst_ut->pth_name == NULL)
			return;
	}

	bcopy(src_ut->pth_name, dst_ut->pth_name, MAXTHREADNAMESIZE);
	return;
}