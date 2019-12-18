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
struct stat {int st_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  twarn (char*) ; 

__attribute__((used)) static int
filesize(char *path)
{
    struct stat s;

    int r = stat(path, &s);
    if (r == -1) {
        twarn("stat");
        exit(1);
    }
    return s.st_size;
}