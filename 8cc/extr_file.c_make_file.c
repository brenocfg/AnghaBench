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
struct stat {int /*<<< orphan*/  st_mtime; } ;
struct TYPE_4__ {char* name; int line; int column; int /*<<< orphan*/  mtime; int /*<<< orphan*/ * file; } ;
typedef  TYPE_1__ File ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

File *make_file(FILE *file, char *name) {
    File *r = calloc(1, sizeof(File));
    r->file = file;
    r->name = name;
    r->line = 1;
    r->column = 1;
    struct stat st;
    if (fstat(fileno(file), &st) == -1)
        error("fstat failed: %s", strerror(errno));
    r->mtime = st.st_mtime;
    return r;
}