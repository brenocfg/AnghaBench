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
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fwrite (char const*,size_t,int,int /*<<< orphan*/ *) ; 

bool write_file(const char *path, const char *buf, size_t len) {
    FILE *file = fopen(path, "w");
    if (!file) {
        return false;
    }
    size_t n = fwrite(buf, len, 1, file);
    fclose(file);
    return n == 1;
}