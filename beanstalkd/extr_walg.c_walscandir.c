#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dirent {scalar_t__ d_name; } ;
typedef  int /*<<< orphan*/  base ;
struct TYPE_3__ {int next; int /*<<< orphan*/  dir; } ;
typedef  TYPE_1__ Wal ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (scalar_t__,char*,int const) ; 
 int strtol (scalar_t__,char**,int) ; 

__attribute__((used)) static int
walscandir(Wal *w)
{
    static char base[] = "binlog.";
    static const int len = sizeof(base) - 1;
    DIR *d;
    struct dirent *e;
    int min = 1<<30;
    int max = 0;
    int n;
    char *p;

    d = opendir(w->dir);
    if (!d) return min;

    while ((e = readdir(d))) {
        if (strncmp(e->d_name, base, len) == 0) {
            n = strtol(e->d_name+len, &p, 10);
            if (p && *p == '\0') {
                if (n > max) max = n;
                if (n < min) min = n;
            }
        }
    }

    closedir(d);
    w->next = max + 1;
    return min;
}