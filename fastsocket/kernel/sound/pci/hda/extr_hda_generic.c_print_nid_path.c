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
struct nid_path {int depth; int* path; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  snd_printdd (char*,char const*,int,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 

__attribute__((used)) static void print_nid_path(const char *pfx, struct nid_path *path)
{
	char buf[40];
	int i;


	buf[0] = 0;
	for (i = 0; i < path->depth; i++) {
		char tmp[4];
		sprintf(tmp, ":%02x", path->path[i]);
		strlcat(buf, tmp, sizeof(buf));
	}
	snd_printdd("%s path: depth=%d %s\n", pfx, path->depth, buf);
}