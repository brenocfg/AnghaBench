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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  format (char*,char*,char*) ; 
 char* fullpath (int /*<<< orphan*/ ) ; 
 scalar_t__ guarded (char*) ; 
 int /*<<< orphan*/  make_file (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ map_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  map_put (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  once ; 
 int /*<<< orphan*/  stream_push (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool try_include(char *dir, char *filename, bool isimport) {
    char *path = fullpath(format("%s/%s", dir, filename));
    if (map_get(once, path))
        return true;
    if (guarded(path))
        return true;
    FILE *fp = fopen(path, "r");
    if (!fp)
        return false;
    if (isimport)
        map_put(once, path, (void *)1);
    stream_push(make_file(fp, path));
    return true;
}