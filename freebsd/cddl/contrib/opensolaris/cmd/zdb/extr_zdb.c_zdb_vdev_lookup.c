#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int vdev_children; char* vdev_path; struct TYPE_4__** vdev_child; } ;
typedef  TYPE_1__ vdev_t ;

/* Variables and functions */
 scalar_t__ strcmp (char*,char const*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 
 char* strrchr (char*,char) ; 
 unsigned int strtoul (char const*,char**,int) ; 

__attribute__((used)) static vdev_t *
zdb_vdev_lookup(vdev_t *vdev, const char *path)
{
	char *s, *p, *q;
	unsigned i;

	if (vdev == NULL)
		return (NULL);

	/* First, assume the x.x.x.x format */
	i = strtoul(path, &s, 10);
	if (s == path || (s && *s != '.' && *s != '\0'))
		goto name;
	if (i >= vdev->vdev_children)
		return (NULL);

	vdev = vdev->vdev_child[i];
	if (*s == '\0')
		return (vdev);
	return (zdb_vdev_lookup(vdev, s+1));

name:
	for (i = 0; i < vdev->vdev_children; i++) {
		vdev_t *vc = vdev->vdev_child[i];

		if (vc->vdev_path == NULL) {
			vc = zdb_vdev_lookup(vc, path);
			if (vc == NULL)
				continue;
			else
				return (vc);
		}

		p = strrchr(vc->vdev_path, '/');
		p = p ? p + 1 : vc->vdev_path;
		q = &vc->vdev_path[strlen(vc->vdev_path) - 2];

		if (strcmp(vc->vdev_path, path) == 0)
			return (vc);
		if (strcmp(p, path) == 0)
			return (vc);
		if (strcmp(q, "s0") == 0 && strncmp(p, path, q - p) == 0)
			return (vc);
	}

	return (NULL);
}