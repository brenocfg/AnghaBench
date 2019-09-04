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
struct vnode {size_t v_type; int v_usecount; int v_writecount; int v_flag; } ;
typedef  int /*<<< orphan*/  sbuf ;

/* Variables and functions */
 int VBWAIT ; 
 int VNOFLUSH ; 
 int VROOT ; 
 int VSYSTEM ; 
 int VTEXT ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 char** typename ; 
 scalar_t__ vnode_isaliased (struct vnode*) ; 

void
vprint(const char *label, struct vnode *vp)
{
	char sbuf[64];

	if (label != NULL)
		printf("%s: ", label);
	printf("type %s, usecount %d, writecount %d",
	       typename[vp->v_type], vp->v_usecount, vp->v_writecount);
	sbuf[0] = '\0';
	if (vp->v_flag & VROOT)
		strlcat(sbuf, "|VROOT", sizeof(sbuf));
	if (vp->v_flag & VTEXT)
		strlcat(sbuf, "|VTEXT", sizeof(sbuf));
	if (vp->v_flag & VSYSTEM)
		strlcat(sbuf, "|VSYSTEM", sizeof(sbuf));
	if (vp->v_flag & VNOFLUSH)
		strlcat(sbuf, "|VNOFLUSH", sizeof(sbuf));
	if (vp->v_flag & VBWAIT)
		strlcat(sbuf, "|VBWAIT", sizeof(sbuf));
	if (vnode_isaliased(vp))
		strlcat(sbuf, "|VALIASED", sizeof(sbuf));
	if (sbuf[0] != '\0')
		printf(" flags (%s)", &sbuf[1]);
}